
#include "ServerRecvProtocol.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

ClientMessage ServerRecvProtocol::receiveMessage(){
    unsigned char type = recv_byte();
    // if(type == MessageType::Input){
    unsigned char action = recv_byte();
    return ClientMessage(type, action);
    // }
}
