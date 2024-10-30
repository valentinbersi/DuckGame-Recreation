#include "GameLoop.h"

#include <memory>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define INITIAL_TICKS 0

#define MILI_TO_SECS 0.001f

float GameLoop::calculateDeltaTime() {
    const u64 frameTicks = SDL_GetTicks64();
    const u64 deltaTime = frameTicks - prevTicks;
    prevTicks = frameTicks;
    return static_cast<float>(deltaTime) * MILI_TO_SECS;
}

void GameLoop::retrieveCurrentFrameCommands() {
    currentFrameCommands = std::move(clientCommands.popAll());
}

void GameLoop::processCurrentFrameCommands() {
    while (!currentFrameCommands.empty()) {
        std::unique_ptr<Command> currentCommand = std::move(currentFrameCommands.front());
        currentFrameCommands.pop();
        // currentCommand->execute(game);
    }
}

void GameLoop::broadcastGameStatus() {
    std::shared_ptr<GameStatus> gameStatus = std::make_shared(std::move(game.status()));
    std::ranges::remove_if(clientQueues, [&gameStatus](const auto& clientQueue) {
        if (clientQueue.expired())
            return true;

        clientQueue.lock()->try_push(gameStatus);
        return false;
    });
}

GameLoop::GameLoop(): prevTicks(INITIAL_TICKS) {}

void GameLoop::run() {
    prevTicks = SDL_GetTicks64();
    game.start();

    while (_keep_running) {
        const float deltaTime = calculateDeltaTime();
        retrieveCurrentFrameCommands();
        processCurrentFrameCommands();
        game.update(deltaTime);
        broadcastGameStatus();
        SDL_Delay(1);
    }
}

void GameLoop::addClient(const u16 clientID,
                         std::weak_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> clientQueue) {
    clientQueues.push_back(std::move(clientQueue));
    game.addPlayer(clientID);
}

BlockingQueue<std::unique_ptr<Command>>* GameLoop::getQueue(){
    return &clientCommands;
}
