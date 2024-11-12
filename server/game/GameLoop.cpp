#include "GameLoop.h"

#include <algorithm>
#include <memory>
#include <utility>

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

GameLoop::GameLoop() = default;

#define FPS 30

void GameLoop::run() {
    try {
        broadcast(std::make_shared<ReplyMessage>(0, 1, 0));
        timer.start();
        game.start();

        while (_keep_running) {
            const float deltaTime = timer.iterationStartSeconds().count();
            retrieveCurrentFrameCommands();
            processCurrentFrameCommands();
            game.updateInternal(deltaTime);
            game.update(deltaTime);
            broadcast(std::make_shared<GameStatus>(std::move(game.status())));
            timer.iterationEnd(FPS);
        }
    } catch (const ClosedQueue& err) {
        // Expected when closing server
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _keep_running = false;
    _is_alive = false;
}

void GameLoop::stop() {
    clientCommands.close();
    _keep_running = false;
    _is_alive = false;
}

bool GameLoop::shouldAddQueue(const u16 clientID) {
    return clientID % 2 == 1;
}

void GameLoop::addClient(const u16 clientID,
                         std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue) {

    game.addPlayer(clientID);
    if(shouldAddQueue(clientID)){
        clientQueuesMap.insert({clientID, std::move(clientQueue)});
    }
    broadcast(std::make_shared<ReplyMessage>(0, 0, game.playersCount()));
}

BlockingQueue<std::unique_ptr<Command>>* GameLoop::getQueue() { return &clientCommands; }

void GameLoop::broadcast(std::shared_ptr<ServerMessage> message) {
    for(auto it = clientQueuesMap.begin(); it != clientQueuesMap.end();){
        if(it->second.expired()){
            try{
                game.removePlayer((it->first)+1);
            } catch (const GameController::PlayerNotFound& err){
                // There was no player 2
            }
            game.removePlayer(it->first);
            it = clientQueuesMap.erase(it);
        } else {
            it->second.lock()->push(message);
            ++it;
        }
    }   
}
