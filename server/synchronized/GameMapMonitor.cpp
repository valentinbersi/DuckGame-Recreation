#include "GameMapMonitor.h"

#include <memory>
#include <random>
#include <ranges>

#include "ReplyMessage.h"

#define PLAYER_COUNT_BEGINING 0
#define RANGE_MATCH_ID 1, 65535
#define MAX_PLAYERS_LOCAL 2
#define P1 0
#define P2 1

RandomIntGenerator GameMapMonitor::randomGenerator(RANGE_MATCH_ID);

GameMapMonitor::NoSpaceLeft::NoSpaceLeft(u16 MatchID):
        std::logic_error("Match " + std::to_string(MatchID) + " is full") {}

GameMapMonitor::AlreadyStarted::AlreadyStarted(u16 MatchID):
        std::logic_error("Match " + std::to_string(MatchID) + " was already started") {}

GameMapMonitor::MatchEnded::MatchEnded(u16 MatchID):
        std::logic_error("Match " + std::to_string(MatchID) + " ended") {}

GameMapMonitor::GameMapMonitor(): levels(LevelData::loadLevels()) {}

BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGame(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId, u8 playerCount) {
    std::vector<DuckData::Id> colors(MAX_PLAYERS_LOCAL, DuckData::Id::None);

    auto& game = gameMap.at(matchID);
    if (game->is_alive()) {
        throw AlreadyStarted(matchID);
    }

    if (game->isJoinable()) {
        throw MatchEnded(matchID);
    }

    if (!game->canJoinGame(playerCount)) {
        throw NoSpaceLeft(matchID);
    }

    for (u8 i = PLAYER_COUNT_BEGINING; i < playerCount; i++) {
        colors[i] = game->addClient(clientId + i, senderQueue);
    }

    senderQueue->push(std::make_unique<ReplyMessage>(matchID, colors[P1], colors[P2]));
    game->JoinTransactionCompleted();
    return game->getQueue();
}

BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::joinGameSafe(
        u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        u16 clientId, u8 playerCount) {
    std::lock_guard lock(mutex);
    return joinGame(matchID, senderQueue, clientId, playerCount);
}
BlockingQueue<std::unique_ptr<Command>>* GameMapMonitor::startGameSafe(u16 matchID) {
    std::lock_guard lock(mutex);

    auto& game = gameMap.at(matchID);
    if (game->is_alive()) {
        throw AlreadyStarted(matchID);
    }
    if (game->isJoinable()) {
        throw MatchEnded(matchID);
    }
    game->start();
    return game->getQueue();
}

void GameMapMonitor::createGameAndJoinSafe(
        std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue, u16 clientId,
        u8 playerCount) {
    std::lock_guard lock(mutex);
    u16 random_number;
    do {
        random_number = randomGenerator.generateRandomInt();
    } while (gameMap.contains(random_number));
    gameMap.insert({random_number, std::make_unique<GameLoop>(levels)});
    joinGame(random_number, senderQueue, clientId, playerCount);
}

void GameMapMonitor::clearGames() {
    std::lock_guard lock(mutex);
    for (auto iter = gameMap.begin(); iter != gameMap.end();) {
        if (!iter->second->is_alive() && iter->second->isJoinable()) {
            iter->second->join();
            iter = gameMap.erase(iter);
        } else {
            iter++;
        }
    }
}

GameMapMonitor::~GameMapMonitor() {
    for (const auto& gameloop: gameMap | std::views::values) {
        gameloop->stop();
        if (gameloop->isJoinable()) {
            gameloop->join();
        }
    }
}
