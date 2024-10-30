#pragma once
#include <unordered_map>
#include <mutex>
#include "GameLoop.h"
#include "Types.h"

class GameMapMonitor{
private:
    std::mutex mutex;
    std::unordered_map<u16, std::unique_ptr<GameLoop>> gameMap;

public:
    GameMapMonitor();

    void accessIfPresent(u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                        u16 clientId);

    void startIfPresent(u16 matchID);

    u16 insertSafe(std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                    u16 clientId);

    ~GameMapMonitor();

};
