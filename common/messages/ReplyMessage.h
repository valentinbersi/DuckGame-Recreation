#pragma once
#include "ServerMessage.h"

struct ReplyMessage: public ServerMessage {
public:
    u16 matchID;

    u8 startGame;

    u8 connectedPlayers;

    ReplyMessage();

    ReplyMessage(u16 id);

    ReplyMessage(u8 connectedPlayers);

    ReplyMessage(u16 id, u8 startGame, u8 connectedPlayers);

    void send(ServerSendProtocol& serverProtocol) override;

    bool operator==(const ReplyMessage& other) const;

    ~ReplyMessage();
};
