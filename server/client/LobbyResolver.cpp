#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(
        GameMapMonitor& gameMap,
        std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue):

        gameMap(gameMap), senderQueue(senderQueue) {}

BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveRequest(const LobbyMessage& message) {
    if (message.request == LobbyRequest::NEWMATCH) {
        u16 matchID = gameMap.creatGameSafe();
        // senderQueue->push(matchID)
        gameMap.joinGameIfCreated(matchID, senderQueue, 0); // aproposito no lo tomo, porque soy host del game.
        return nullptr;
    } else if (message.request == LobbyRequest::JOINMATCH) {
        return gameMap.joinGameIfCreated(message.matchId, senderQueue, 0);  
    } else {                                                        
        return gameMap.startGameIfCreated(message.matchId);
    }
}