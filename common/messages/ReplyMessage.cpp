#include "ReplyMessage.h"

#define NO_MATCHID 0
#define NO_START_GAME 0

ReplyMessage::ReplyMessage() : ServerMessage(MessageType::Reply), matchID(NO_MATCHID), startGame(NO_START_GAME) {}

ReplyMessage::ReplyMessage(u16 id, u8 startGame) : ServerMessage(MessageType::Reply), matchID(id), startGame(startGame) {}

void ReplyMessage::send(ServerSendProtocol& serverProtocol) {
    serverProtocol.sendReplyMessage(matchID, startGame);
}

ReplyMessage::~ReplyMessage() {}