#include "LobbyMessage.h"

LobbyMessage::LobbyMessage():
        ClientMessage(MessageType::Lobby),
        request(LobbyRequest::NEWMATCH),
        playerCount(0),
        matchId(0),
        color() {}

LobbyMessage::LobbyMessage(LobbyRequest request, u8 count, u16 id, DuckData::Id color):
        ClientMessage(MessageType::Lobby),
        request(request),
        playerCount(count),
        matchId(id),
        color(color) {}

void LobbyMessage::send(ClientSendProtocol& clientProtocol) {
    clientProtocol.sendLobbyMessage(type, request, playerCount, matchId, static_cast<u8> (color));
}

bool LobbyMessage::operator==(const LobbyMessage& other) const {
    return type == other.type && 
           request == other.request && 
           playerCount == other.playerCount &&
           matchId == other.matchId &&
           color == other.color;
}

LobbyMessage::~LobbyMessage() = default;
