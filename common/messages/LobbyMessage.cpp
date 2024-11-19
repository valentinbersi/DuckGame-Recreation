#include "LobbyMessage.h"

LobbyMessage::LobbyMessage():
        ClientMessage(MessageType::Lobby),
        request(),
        playerCount(0),
        player1Name(""),
        player2Name(""),
        matchId(0) {}

LobbyMessage::LobbyMessage(LobbyRequest request, u8 count, std::string name1, std::string name2,
                           u16 id):
        ClientMessage(MessageType::Lobby),
        request(request),
        playerCount(count),
        player1Name(name1),
        player2Name(name2),
        matchId(id) {}

void LobbyMessage::send(ClientSendProtocol& clientProtocol) {
    clientProtocol.sendLobbyMessage(type, request, playerCount, player1Name, player2Name, matchId);
}

bool LobbyMessage::operator==(const LobbyMessage& other) const {
    return type == other.type && request == other.request && playerCount == other.playerCount &&
           player1Name == other.player1Name && player2Name == other.player2Name &&
           matchId == other.matchId;
}

LobbyMessage::~LobbyMessage() {}