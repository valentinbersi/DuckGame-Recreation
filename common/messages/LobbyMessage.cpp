#include "LobbyMessage.h"

LobbyMessage::LobbyMessage():
        ClientMessage(MessageType::Lobby),
        request(LobbyRequest::NEWMATCH),
        playerCount(0),
        matchId(0) {}

LobbyMessage::LobbyMessage(LobbyRequest request, u8 count, u16 id):
        ClientMessage(MessageType::Lobby),
        request(request),
        playerCount(count),
        matchId(id) {}

void LobbyMessage::send(ClientSendProtocol& clientProtocol) {
    clientProtocol.sendLobbyMessage(type, request, playerCount, matchId);
}

bool LobbyMessage::operator==(const LobbyMessage& other) const {
    return type == other.type && 
           request == other.request && 
           playerCount == other.playerCount &&
           matchId == other.matchId;
}

LobbyMessage::~LobbyMessage() = default;
