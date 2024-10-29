
#include "Receiver.h"

Receiver::Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queue_ptr,
                   BlockingQueue<std::unique_ptr<GameStatus>> queueSender /*mapa de partidas.*/): 
    recvProtocol(socket),
    gameQueue(queue_ptr),
    lobby(/*queue del sender y el mapa.*/) {}

void Receiver::run(){
    try{
        while(_keep_running){
            //se viene refactor
            ClientMessage message = recvProtocol.receiveMessage();
            // std::unique_ptr<Command> = factory.makeCommand(message);
            // gamequeue.push()
        }

    // }catch(){

    }catch(...){

    }
}