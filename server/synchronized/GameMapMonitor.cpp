#include "GameMapMonitor.h"

#include <memory>
#include <random>

#include "ReplyMessage.h"

#define PLAYER_COUNT_BEGINING 0
#define MIN_MATCH_ID 1
#define MAX_MATCH_ID 65535

GameMapMonitor::GameMapMonitor() : levels(LevelData::loadLevels()) {}

BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGameIfCreated(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId, u8 playerCount) {
    std::lock_guard lock(mutex);

    if (gameMap.find(matchID) != gameMap.end()) {
        senderQueue->push(std::make_shared<ReplyMessage>(matchID));
        for (u8 i = PLAYER_COUNT_BEGINING; i < playerCount; i++) {
            gameMap.at(matchID)->addClient(clientId + i, senderQueue);
        }
        return gameMap.at(matchID)->getQueue();
    }
    senderQueue->push(std::make_shared<ReplyMessage>());
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
        std::uniform_int_distribution<uint16_t> dist(MIN_MATCH_ID, MAX_MATCH_ID);
        random_number = dist(gen);

    } while (gameMap.contains(random_number));
    gameMap.insert({random_number, std::make_unique<GameLoop>(levels)});
    return random_number;
}

GameMapMonitor::~GameMapMonitor() {
    for (auto& [_, game]: gameMap) {
        game->stop();
        if (game->isJoinable()) {
            game->join();
        }
    }
}
