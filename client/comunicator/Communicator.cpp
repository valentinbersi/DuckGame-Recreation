#include "Communicator.h"

Communicator::Communicator(ActiveSocket&& socket) : skt(std::move(socket)), 
                                                    sendQueue(), 
                                                    recvQueue(),
                                                    sender(skt,sendQueue),
                                                    receiver(skt,recvQueue)
{
    sender.start();
    receiver.start();     
}

bool Communicator::trysend(ClientMessage& message){
    return sendQueue.try_push(message);
}

std::optional<GameStatus> Communicator::tryrecv(){
    return recvQueue.try_pop();
}

Communicator::~Communicator(){
    sender.stop();
    receiver.stop();
    skt.close();
    sendQueue.close();
    recvQueue.close();
    sender.join();
    receiver.join();
}
                                                