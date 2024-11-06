#include "GameLoop.h"

#include <memory>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "GameStatus.h"
#include "ReplyMessage.h"

float GameLoop::calculateDeltaTime() {
    const std::chrono::steady_clock::time_point frameTicks = std::chrono::steady_clock::now();
    const std::chrono::duration<float> deltaTime = frameTicks - prevTicks;
    prevTicks = frameTicks;
    return deltaTime.count();
}

void GameLoop::retrieveCurrentFrameCommands() {
    currentFrameCommands = std::move(clientCommands.popAll());
}

void GameLoop::processCurrentFrameCommands() {
    while (!currentFrameCommands.empty()) {
        std::unique_ptr<Command> currentCommand = std::move(currentFrameCommands.front());
        currentFrameCommands.pop();
        currentCommand->execute(game);
    }
}

void GameLoop::broadcastGameStatus() {
    auto gameStatus = std::make_shared<GameStatus>(std::move(game.status()));
    std::ranges::remove_if(clientQueues, [&gameStatus](const auto& clientQueue) {
        if (clientQueue.expired())
            return true;

        clientQueue.lock()->try_push(gameStatus);
        return false;
    });
}

GameLoop::GameLoop(): prevTicks(std::chrono::milliseconds::zero()) {}

void GameLoop::run() {
    broadcastStartGame();
    prevTicks = std::chrono::steady_clock::now();
    game.start();

    while (_keep_running) {
        const float deltaTime = calculateDeltaTime();
        retrieveCurrentFrameCommands();
        processCurrentFrameCommands();
        game.updateInternal(deltaTime);
        game.update(deltaTime);
        broadcastGameStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(30));  // 30 fps aprox
    }
}

void GameLoop::addClient(const u16 clientID,
                         std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue) {
    clientQueues.push_back(std::move(clientQueue));
    game.addPlayer(clientID);
}

BlockingQueue<std::unique_ptr<Command>>* GameLoop::getQueue() { return &clientCommands; }

void GameLoop::broadcastStartGame() {
    std::shared_ptr<ServerMessage> startMessage = std::make_shared<ReplyMessage>(1, 1);
    clientQueues.remove_if([&startMessage](const auto& clientQueue) {
        if (clientQueue.expired()) {
            return true;
        }
        clientQueue.lock()->try_push(startMessage);
        return false;
    });
}
