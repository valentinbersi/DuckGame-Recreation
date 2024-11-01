#include "ServerRecvProtocol.h"
#include "LobbyMessage.h"
#include "GameMessage.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

std::unique_ptr<ClientMessage> ServerRecvProtocol::receiveMessage() {
    MessageType type = recv_byte();
    if(type == MessageType::Lobby){
        LobbyRequest request = recv_byte();
        u8 playerCount = recv_byte();
        std::string name1 = recv_string(); 
        std::string name2 = recv_string(); 
        u16 matchID = recvShort();
        return std::make_unique<LobbyMessage>(request, playerCount, name1, name2, matchID);
    }
    return std::make_unique<GameMessage>(recv_byte());
}
