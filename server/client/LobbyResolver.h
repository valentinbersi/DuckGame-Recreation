#pragma once
#include "GameLoop.hpp"
#include "GameStatus.hpp"
#include "ClientMessage.h"
#include "LobbyMessage.h"
#include "GameMessage.h" 
#include "ThreadSafeHashMap.h"
#include "BlockingQueue.h"
#include <memory>
#include "Types.h"

class LobbyResolver{
private:
    ThreadSafeMap<u16, std::unique_ptr<GameLoop>>& gameMap;
    std::weak_ptr<BlockingQueue<GameStatus>> senderQueue;
    BlockingQueue<std::unique_ptr<Command>>* recvQueue; //empieza en nullptr

    void resolveNewMatch();

    void resolveJoinMatch();

    void resolverStartMatch();

public:
    LobbyResolver(ThreadSafeMap<u16, std::unique_ptr<GameLoop>>& gameMap,
                  std::weak_ptr<BlockingQueue<GameStatus>> senderQueue,
                  BlockingQueue<std::unique_ptr<Command>>* recvQueue);

    void resolveRequest(const LobbyMessage& request);

    ~LobbyResolver();

};
