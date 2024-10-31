#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(
        GameMapMonitor& gameMap,
        std::shared_ptr<BlockingQueue<std::shared_ptr<Message>>> senderQueue,
        BlockingQueue<std::unique_ptr<Command>>* recvQueue):

        gameMap(gameMap), senderQueue(senderQueue), recvQueue(recvQueue) {}

void LobbyResolver::resolveRequest(const LobbyMessage& message) {
    if (message.request == LobbyRequest::NEWMATCH) {
        u16 matchID = gameMap.creatGameSafe();
        recvQueue = gameMap.joinGameIfCreated(matchID, senderQueue, 0);  // el ultimo es client id.
        // senderQueue->push(matchID) aca hay que hacer la parte de herencia.
    } else if (message.request == LobbyRequest::JOINMATCH) {
        gameMap.joinGameIfCreated(message.matchId, senderQueue, 0);  // idem antes
    } else {                                                         // start game
        gameMap.startGameIfCreated(message.matchId);
    }
}