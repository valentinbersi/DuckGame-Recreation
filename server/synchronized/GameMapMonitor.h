#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "GameLoop.h"
#include "LevelData.h"
#include "RandomGenerator.h"
#include "ServerMessage.h"
#include "Types.h"

class GameMapMonitor {
private:
    std::mutex mutex;
    std::unordered_map<u16, std::unique_ptr<GameLoop>> gameMap;
    std::vector<LevelData> levels;
    static RandomIntGenerator randomGenerator;

public:
    GameMapMonitor();

    BlockingQueue<std::unique_ptr<Command>>* joinGameIfCreated(
            u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

    BlockingQueue<std::unique_ptr<Command>>* startGameIfCreated(u16 matchID);

    u16 creatGameSafe();

    ~GameMapMonitor();
};
