#include "ReplyMessage.h"

#define NO_MATCHID 0
#define NO_START_GAME 0
#define START_GAME 1
#define NO_CONNECTED_PLAYERS 0
#define NO_ERROR " "

const ReplyMessage ReplyMessage::startGameInstance = ReplyMessage(NO_MATCHID, START_GAME, NO_CONNECTED_PLAYERS, DuckData::Id::None, DuckData::Id::None, NO_ERROR);

ReplyMessage::ReplyMessage():
        ServerMessage(MessageType::Reply),
        matchID(NO_MATCHID),
        startGame(NO_START_GAME),
        connectedPlayers(NO_CONNECTED_PLAYERS),
        color1(DuckData::Id::None),
        color2(DuckData::Id::None),
        error(NO_ERROR) {}

ReplyMessage::ReplyMessage(u16 id, DuckData::Id color1, DuckData::Id color2):
        ServerMessage(MessageType::Reply),
        matchID(id),
        startGame(NO_START_GAME),
        connectedPlayers(NO_CONNECTED_PLAYERS),
        color1(color1),
        color2(color2),
        error(NO_ERROR) {}

ReplyMessage::ReplyMessage(std::string error):
        ServerMessage(MessageType::Reply),
        matchID(NO_MATCHID),
        startGame(NO_START_GAME),
        connectedPlayers(NO_CONNECTED_PLAYERS),
        color1(DuckData::Id::None),
        color2(DuckData::Id::None),
        error(error) {}

ReplyMessage::ReplyMessage(u8 connectedPlayers):
        ServerMessage(MessageType::Reply),
        matchID(NO_MATCHID),
        startGame(NO_START_GAME),
        connectedPlayers(connectedPlayers),
        color1(DuckData::Id::None),
        color2(DuckData::Id::None),
        error(NO_ERROR) {}

ReplyMessage::ReplyMessage(u16 id, u8 startGame, u8 connectedPlayers, DuckData::Id color1, DuckData::Id color2, std::string error):
        ServerMessage(MessageType::Reply),
        matchID(id),
        startGame(startGame),
        connectedPlayers(connectedPlayers),
        color1(color1),
        color2(color2),
        error(error) {}

void ReplyMessage::send(ServerSendProtocol& serverProtocol) {
    serverProtocol.sendReplyMessage(matchID, startGame, connectedPlayers, color1, color2, error);
}

bool ReplyMessage::operator==(const ReplyMessage& other) const {
    return type == other.type && 
           matchID == other.matchID && 
           startGame == other.startGame &&
           connectedPlayers == other.connectedPlayers &&
           color1 == other.color1 &&
           color2 == other.color2 &&
           error == other.error;
}

ReplyMessage::~ReplyMessage() = default;
