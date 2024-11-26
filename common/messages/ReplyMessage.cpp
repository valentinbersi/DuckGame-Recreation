#include "ReplyMessage.h"

#define NO_MATCHID 0
#define NO_START_GAME 0
#define NO_CONNECTED_PLAYERS 0
#define NO_SUCESS 0

ReplyMessage::ReplyMessage():
        ServerMessage(MessageType::Reply),
        matchID(NO_MATCHID),
        startGame(NO_START_GAME),
        connectedPlayers(NO_CONNECTED_PLAYERS),
        couldPickColor(NO_SUCESS) {}

ReplyMessage::ReplyMessage(u16 id, u8 couldPickColor):
        ServerMessage(MessageType::Reply),
        matchID(id),
        startGame(NO_START_GAME),
        connectedPlayers(NO_CONNECTED_PLAYERS),
        couldPickColor(couldPickColor) {}

ReplyMessage::ReplyMessage(u8 connectedPlayers):
        ServerMessage(MessageType::Reply),
        matchID(NO_MATCHID),
        startGame(NO_START_GAME),
        connectedPlayers(connectedPlayers),
        couldPickColor(NO_SUCESS) {}

ReplyMessage::ReplyMessage(u16 id, u8 startGame, u8 connectedPlayers, u8 couldPickColor):
        ServerMessage(MessageType::Reply),
        matchID(id),
        startGame(startGame),
        connectedPlayers(connectedPlayers),
        couldPickColor(couldPickColor) {}

void ReplyMessage::send(ServerSendProtocol& serverProtocol) {
    serverProtocol.sendReplyMessage(matchID, startGame, connectedPlayers, couldPickColor);
}

bool ReplyMessage::operator==(const ReplyMessage& other) const {
    return type == other.type && matchID == other.matchID && startGame == other.startGame &&
           connectedPlayers == other.connectedPlayers && couldPickColor == other.couldPickColor;
}

ReplyMessage::~ReplyMessage() = default;
