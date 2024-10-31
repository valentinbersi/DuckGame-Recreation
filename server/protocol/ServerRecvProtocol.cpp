#include "ServerRecvProtocol.h"
#include "LobbyMessage.h"
#include "GameMessage.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

std::unique_ptr<Message> ServerRecvProtocol::receiveMessage() {
    MessageType type = recv_byte();
    if(type == MessageType::Lobby){
        LobbyRequest request = recv_byte();
        std::string usrName = recv_string(); 
        u16 matchid = recvShort();
        return std::make_unique<LobbyMessage>(request,usrName, matchid);
    }
    return std::make_unique<GameMessage>(recv_byte());
}
