#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(ThreadSafeMap<u16, std::unique_ptr<GameLoop>>& gameMap,
                            std::weak_ptr<BlockingQueue<GameStatus>> senderQueue,
                            BlockingQueue<std::unique_ptr<Command>>* recvQueue):
                            
                            gameMap(gameMap),
                            senderQueue(senderQueue),
                            recvQueue(recvQueue) {}

void LobbyResolver::resolveRequest(const LobbyMessage& message){
    if (message.request == LobbyRequest::NEWMATCH) {

    }else if(message.request == LobbyRequest::JOINMATCH){

    }else{ // start game
        
    }
}