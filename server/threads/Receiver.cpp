
#include "Receiver.h"

Receiver::Receiver(ActiveSocket& socket): protocol(socket) {}

void Receiver::run(){
    try{
        while(_keep_running){
            ClientMessage message = protocol.receiveMessage();
            // std::unique_ptr<Command> = factory.makeCommand(message);
            // gamequeue.push()
        }

    // }catch(){

    }catch(...){

    }
}