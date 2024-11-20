#include "ServerRecvProtocol.h"

#include <string>

#include "GameMessage.h"
#include "LobbyMessage.h"

ServerRecvProtocol::ServerRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

GameMessage ServerRecvProtocol::receiveGameMessage() {
    recvByte();  // el type
    u8 action = recvByte();
    u8 player = recvByte();
    return GameMessage(action, player);
}

LobbyMessage ServerRecvProtocol::receiveLobbyMessage() {
    recvByte();  // el type
    LobbyRequest request = recvByte();
    u8 playerCount = recvByte();
    std::string name1 = recv_string();
    std::string name2 = recv_string();
    u16 matchID = recvShort();
    return LobbyMessage(request, playerCount, name1, name2, matchID);
}
