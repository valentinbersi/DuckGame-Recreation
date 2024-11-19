#pragma once
#include <memory>
#include <unordered_map>

#include "BlockingQueue.h"
#include "GameLoop.h"
#include "GameMapMonitor.h"
#include "GameMessage.h"
#include "LobbyMessage.h"
#include "ReplyMessage.h"
#include "ServerMessage.h"
#include "Types.h"

class LobbyResolver {
private:
    GameMapMonitor& gameMap;
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue;
    const u16& clientID;
    std::unordered_map<LobbyRequest::Value, std::function<BlockingQueue<std::unique_ptr<Command>>*(
                                                    const LobbyMessage& request)>>
            resolveMap;

    BlockingQueue<std::unique_ptr<Command>>* resolveNewMatch(const LobbyMessage& request);

    BlockingQueue<std::unique_ptr<Command>>* resolveJoinMatch(const LobbyMessage& request);

    BlockingQueue<std::unique_ptr<Command>>* resolveStartMatch(const LobbyMessage& request);

public:
    LobbyResolver(GameMapMonitor& gameMap,
                  std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
                  const u16& clientID);

    BlockingQueue<std::unique_ptr<Command>>* resolveRequest(const LobbyMessage& request);

    ~LobbyResolver(){};
};
