#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(GameMapMonitor& gameMap,
                            std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                            BlockingQueue<std::unique_ptr<Command>>* recvQueue):
                            
                            gameMap(gameMap),
                            senderQueue(senderQueue),
                            recvQueue(recvQueue) {}

void LobbyResolver::resolveRequest(const LobbyMessage& message){
    if (message.request == LobbyRequest::NEWMATCH) {
        gameMap.insertSafe();
    }else if(message.request == LobbyRequest::JOINMATCH){
        gameMap.accessIfPresent();
    }else{ // start game
        gameMap.startIfPresent();
    }
}