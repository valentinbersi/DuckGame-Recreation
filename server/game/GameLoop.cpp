#include "GameLoop.h"

#include <memory>
#include <algorithm>
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
    try{
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
    }catch(const ClosedQueue& err){
        //Expected when closing server
    }catch(...){
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

void GameLoop::addClient(const u16 clientID,
                         std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue) {
    game.addPlayer(clientID);
    auto it = std::find_if(clientQueues.begin(), clientQueues.end(), [&clientQueue](const auto& queue) {
                            return queue.lock() == clientQueue.lock();});
                            
    if (it == clientQueues.end()) {
        clientQueues.push_back(std::move(clientQueue));
    }

    broadcast(std::make_shared<ReplyMessage>(0, 0, game.playersCount()));   
}

BlockingQueue<std::unique_ptr<Command>>* GameLoop::getQueue() { return &clientCommands; }

void GameLoop::broadcast(std::shared_ptr<ServerMessage> message) {
    clientQueues.remove_if([&message](const auto& clientQueue) {
        if (clientQueue.expired()) {
            return true;
        }
        clientQueue.lock()->try_push(message);
        return false;
    });
}
