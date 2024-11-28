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
    std::unordered_map<LobbyRequest::Value,
                       std::function<std::optional<BlockingQueue<std::unique_ptr<Command>>*>(
                               const LobbyMessage& request)>>
            resolveMap;

    /**
     * Resolves a new match request
     * @param request The request
     * @return The queue to the GameLoop
     */
    std::optional<BlockingQueue<std::unique_ptr<Command>>*> resolveNewMatch(
            const LobbyMessage& request);

    /**
     * Resolves a join match request
     * @param request The request
     * @return The queue to the GameLoop
     */
    std::optional<BlockingQueue<std::unique_ptr<Command>>*> resolveJoinMatch(
            const LobbyMessage& request);

    /**
     * Resolves a start match request
     * @param request The request
     * @return The queue to the GameLoop
     */
    std::optional<BlockingQueue<std::unique_ptr<Command>>*> resolveStartMatch(
            const LobbyMessage& request);


public:
    /**
     * Creates a new LobbyResolver
     * @param gameMap The game map
     * @param senderQueue The queue to send messages to the client
     * @param clientID The id of the client
     */
    LobbyResolver(GameMapMonitor& gameMap,
                  std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
                  const u16& clientID);


    /**
     * Resolves a request
     * @param request The request
     * @return The queue to the GameLoop
     */
    std::optional<BlockingQueue<std::unique_ptr<Command>>*> resolveRequest(
            const LobbyMessage& request);

    ~LobbyResolver();
};
