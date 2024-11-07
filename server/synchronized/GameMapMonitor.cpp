#include "GameMapMonitor.h"

#include <random>

#define PLAYER_COUNT_BEGINING 0
GameMapMonitor::GameMapMonitor() {}


BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGameIfCreated(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId, u8 playerCount) {
    std::lock_guard lock(mutex);

    if (gameMap.find(matchID) != gameMap.end()) {
        for(u8 i = PLAYER_COUNT_BEGINING; i < playerCount; i++) {
            gameMap.at(matchID)->addClient(clientId, senderQueue);
        }
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
    u16 random_number;
    do {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint16_t> dist(1, 65535);
        random_number = dist(gen);

    } while (gameMap.contains(random_number));
    gameMap.insert({random_number, std::make_unique<GameLoop>()});
    return random_number;
}

GameMapMonitor::~GameMapMonitor() {
    // joinear values.
}