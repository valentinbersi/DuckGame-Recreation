#include "ServerRecvProtocol.h"

#include "GameMessage.h"
#include "LobbyMessage.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

GameMessage ServerRecvProtocol::receiveGameMessage() {
    recv_byte(); // el type
    u8 action = recv_byte();
    u8 player = recv_byte();
    return GameMessage(action, player);
}

LobbyMessage ServerRecvProtocol::receiveLobbyMessage() {
    recv_byte(); // el type
    LobbyRequest request = recv_byte();
    u8 playerCount = recv_byte();
    std::string name1 = recv_string();
    std::string name2 = recv_string();
    u16 matchID = recvShort();
    return LobbyMessage(request, playerCount, name1, name2, matchID);
}

//Should not be necessary to have this method.
std::unique_ptr<ClientMessage> ServerRecvProtocol::receiveMessage() {
    MessageType type = recv_byte();
    if (type == MessageType::Lobby) {
        LobbyRequest request = recv_byte();
        u8 playerCount = recv_byte();
        std::string name1 = recv_string();
        std::string name2 = recv_string();
        u16 matchID = recvShort();
        return std::make_unique<LobbyMessage>(request, playerCount, name1, name2, matchID);
    }
    u8 action = recv_byte();
    u8 player = recv_byte();
    return std::make_unique<GameMessage>(action, player);
}
