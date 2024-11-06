#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(
        GameMapMonitor& gameMap,
        std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue, const u16& clientID):

        gameMap(gameMap), senderQueue(senderQueue), clientID(clientID) {}

BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveRequest(const LobbyMessage& message) {
    if (message.request == LobbyRequest::NEWMATCH) {
        u16 matchID = gameMap.creatGameSafe();
        senderQueue->push(std::make_shared<ReplyMessage>(matchID, 0));
        gameMap.joinGameIfCreated(matchID, senderQueue, clientID); // aproposito no lo tomo, porque soy host del game.
        return nullptr;
    } else if (message.request == LobbyRequest::JOINMATCH) {
        return gameMap.joinGameIfCreated(message.matchId, senderQueue, clientID);  
    } else {                                                        
        return gameMap.startGameIfCreated(message.matchId);
    }
}