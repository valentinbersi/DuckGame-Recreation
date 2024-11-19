#pragma once
#include <mutex>
#include <unordered_map>

#include "GameLoop.h"
#include "ServerMessage.h"
#include "Types.h"
#include "Level.h"

class GameMapMonitor {
private:
    std::mutex mutex;
    std::unordered_map<u16, std::unique_ptr<GameLoop>> gameMap;
    std::vector<Level> levels;
    
public:
    GameMapMonitor();

    BlockingQueue<std::unique_ptr<Command>>* joinGameIfCreated(
            u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

    BlockingQueue<std::unique_ptr<Command>>* startGameIfCreated(u16 matchID);

    u16 creatGameSafe();

    ~GameMapMonitor();
};
