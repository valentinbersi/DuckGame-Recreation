#include "GameLoop.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include <syslog.h>

#include "GameStatus.h"
#include "ReplyMessage.h"

#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."

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

GameLoop::GameLoop(std::vector<LevelData>& levels): game(levels) {}

void GameLoop::broadcast(std::shared_ptr<ServerMessage> message) {
    for (auto it = clientQueuesMap.begin(); it != clientQueuesMap.end();) {
        if (it->second.expired()) {
            it = clientQueuesMap.erase(it);
        } else {
            bool sucess = it->second.lock()->try_push(message);
            it = sucess ? ++it : clientQueuesMap.erase(it);
        }
    }
}

void GameLoop::processRound(const float deltaTime) {
    game.updateInternal(deltaTime);
    game.update(deltaTime);
    broadcast(std::make_shared<GameStatus>(std::move(game.status())));
}

void GameLoop::loadNewStateIfOver() {
    if (!game.roundInProgress()) {
        game.loadNewState();
    }
}

#define FPS 30

void GameLoop::run() {
    try {
        broadcast(std::make_shared<ReplyMessage>(ReplyMessage::startGameInstance));
        timer.start();
        game.start();

        while (!game.gameEnded() && _keep_running) {
            const float deltaTime = timer.iterationStartSeconds().count();
            retrieveCurrentFrameCommands();
            processCurrentFrameCommands();
            if (game.roundInProgress()) {
                processRound(deltaTime);
                loadNewStateIfOver();
                timer.iterationEnd(FPS);
            }
        }

    } catch (const ClosedQueue& err) {
        // Expected when closing server
    } catch (const std::exception& err) {
        syslog(LOG_CRIT, "%s", err.what());
    }
    _keep_running = false;
    _is_alive = false;
}

void GameLoop::stop() {
    clientCommands.close();
    _keep_running = false;
    _is_alive = false;
}

bool GameLoop::shouldAddQueue(const u16 clientID) { return clientID % 2 == 1; }

bool GameLoop::canJoinGame(const u8 playerAmount) { return !game.exceedsPlayerMax(playerAmount); }

DuckData::Id GameLoop::addClient(
        const u16 clientID,
        std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue) {

    if (shouldAddQueue(clientID)) {
        clientQueuesMap.insert({clientID, std::move(clientQueue)});
    }
    return game.addPlayer(clientID);
}

BlockingQueue<std::unique_ptr<Command>>* GameLoop::getQueue() { return &clientCommands; }

void GameLoop::JoinTransactionCompleted() {
    broadcast(std::make_shared<ReplyMessage>(game.playersCount()));
}
