#include "GameLoop.h"

#include <memory>
#include <utility>

#include "GameStatus.h"
#include "ReplyMessage.h"

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

GameLoop::GameLoop() = default;

#define FPS 240

void GameLoop::run() {
    broadcastStartGame();
    timer.start();
    game.start();

    while (_keep_running) {
        const float deltaTime = timer.iterationStartSeconds().count();
        retrieveCurrentFrameCommands();
        processCurrentFrameCommands();
        game.updateInternal(deltaTime);
        game.update(deltaTime);
        broadcastGameStatus();
        timer.iterationEnd(FPS);
    }
}

void GameLoop::addClient(const u16 clientID,
                         std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue) {
    game.addPlayer(clientID);
    for (const auto& queue: clientQueues) {
        if (queue.lock().get() == clientQueue.lock().get()) {
            return;
        }
    }
    clientQueues.push_back(std::move(clientQueue));
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
