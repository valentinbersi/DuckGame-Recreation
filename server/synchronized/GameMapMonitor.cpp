#include "GameMapMonitor.h"

#include <random>


GameMapMonitor::GameMapMonitor() {}


BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGameIfCreated(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId) {
    std::lock_guard lock(mutex);

    if (gameMap.find(matchID) != gameMap.end()) {
        gameMap.at(matchID)->addClient(clientId,senderQueue);
        return gameMap.at(matchID)->getQueue();
    }
    return nullptr;
}

BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::startGameIfCreated(u16 matchID) {
    std::lock_guard lock(mutex);
    if (gameMap.find(matchID) != gameMap.end()) {
        gameMap.at(matchID)->start();
        return gameMap.at(matchID)->getQueue();
    }
    return nullptr;
}

u16 GameMapMonitor::creatGameSafe() {
    std::lock_guard lock(mutex);
    // u16 random_number;
    // // do {
    // //     std::random_device rd;
    // //     std::mt19937 gen(rd());
    // //     std::uniform_int_distribution<uint16_t> dist(1, 65535);
    // //     random_number = dist(gen);

    // // } while (gameMap.contains(random_number));
    gameMap.insert({1,std::make_unique<GameLoop>()});
    return 1; //va random number
}

GameMapMonitor::~GameMapMonitor() {
    // joinear values. 
}