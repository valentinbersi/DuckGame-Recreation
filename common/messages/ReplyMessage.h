#pragma once
#include "ServerMessage.h"

struct ReplyMessage: public ServerMessage {
public:
    u16 matchID;

    u8 startGame;

    u8 connectedPlayers;

    // 0 if the player could not pick a color, 1 if the player could pick a color
    u8 couldPickColor;

    ReplyMessage();

    explicit ReplyMessage(u16 id, u8 couldPickColor);

    explicit ReplyMessage(u8 connectedPlayers);

    ReplyMessage(u16 id, u8 startGame, u8 connectedPlayers, u8 couldPickColor);


    /**
     * Send ReplyMessage using given Protocol.
     * @param serverProtocol Protocol to send the message.
     */
    void send(ServerSendProtocol& serverProtocol) override;

    /**
     * Compare two ReplyMessages.
     * @param other ReplyMessage to compare.
     * @return True if both ReplyMessages are equal, false otherwise.
     */
    bool operator==(const ReplyMessage& other) const;

    ~ReplyMessage();
};
