#include "GameMapMonitor.h"
#include "ReplyMessage.h"

#include <random>

#define PLAYER_COUNT_BEGINING 0

GameMapMonitor::GameMapMonitor() {}


BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGameIfCreated(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId, u8 playerCount) {
    std::lock_guard lock(mutex);

    if (gameMap.find(matchID) != gameMap.end()) {
        senderQueue->push(std::make_shared<ReplyMessage>(matchID, 0, 0));
        for(u8 i = PLAYER_COUNT_BEGINING; i < playerCount; i++) {
            gameMap.at(matchID)->addClient(clientId+i, senderQueue);
        }
        return gameMap.at(matchID)->getQueue();
    }
    senderQueue->push(std::make_shared<ReplyMessage>(0, 0, 0));
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

void GameMapMonitor::stopAllGames() {
    std::lock_guard lock(mutex);
    for(auto& [key, value] : gameMap) {
        value->stop();
    }
}   

GameMapMonitor::~GameMapMonitor() {
    for(auto& [key, value] : gameMap) {
        if (value->isJoinable()) {
            value->join();
        }
    }
}