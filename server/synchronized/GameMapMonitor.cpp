#include "GameMapMonitor.h"
#include <random>


GameMapMonitor::GameMapMonitor(){}


void GameMapMonitor::accessIfPresent(u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                        u16 clientId){
    std::lock_guard lock(mutex);
    if (gameMap.find(matchID) != gameMap.end()){
        // gameMap[matchID]->addClient(clienId,matchId);
    }  

}

void GameMapMonitor::startIfPresent(u16 matchID){
    std::lock_guard lock(mutex);
    if (gameMap.find(matchID) != gameMap.end()){
        gameMap[matchID]->start();
    }  
}

u16 GameMapMonitor::insertSafe(std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> senderQueue,
                        u16 clientId){
    std::lock_guard lock(mutex);
    u16 random_number;
    do{
        std::lock_guard lock(mutex);
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<uint16_t> dist(1, 65535); 
        uint16_t random_number = dist(gen);

    } while(gameMap.contains(random_number));
    std::unique_ptr<GameLoop> gameloop = std::make_unique<GameLoop>();
    // gameloop->addClient(clientId, senderQueue);
    gameMap[random_number] = std::move(gameloop);
    return random_number;
}

GameMapMonitor::~GameMapMonitor(){
 //creo que todo esta raii
}