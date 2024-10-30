#pragma once
#include "GameLoop.h"
#include "GameStatus.h"
#include "ClientMessage.h"
#include "LobbyMessage.h"
#include "GameMessage.h" 
#include "GameMapMonitor.h"
#include "BlockingQueue.h"
#include <memory>
#include "Types.h"

class LobbyResolver{
private:
    GameMapMonitor& gameMap;
    std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue;
    BlockingQueue<std::unique_ptr<Command>>* recvQueue; //empieza en nullptr

    void resolveNewMatch();

    void resolveJoinMatch();

    void resolverStartMatch();

public:
    LobbyResolver(GameMapMonitor& gameMap,
                  std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                  BlockingQueue<std::unique_ptr<Command>>* recvQueue);

    void resolveRequest(const LobbyMessage& request);

    ~LobbyResolver();

};
