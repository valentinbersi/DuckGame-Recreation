#include "ServerRecvProtocol.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

Message ServerRecvProtocol::receiveMessage(){
    unsigned char type = recv_byte();
    unsigned char action = recv_byte();
    return Message(type, action);
}
