
#include "Receiver.h"

Receiver::Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queue_ptr): 
    recvProtocol(socket),
    gameQueue(queue_ptr) {}

void Receiver::run(){
    try{
        while(_keep_running){
            ClientMessage message = recvProtocol.receiveMessage();
            // std::unique_ptr<Command> = factory.makeCommand(message);
            // gamequeue.push()
        }

    // }catch(){

    }catch(...){

    }
}