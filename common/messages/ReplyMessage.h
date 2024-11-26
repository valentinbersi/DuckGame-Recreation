#pragma once
#include "ServerMessage.h"
#include <string>

struct ReplyMessage: public ServerMessage {
public:
    u16 matchID;

    u8 startGame;

    u8 connectedPlayers;

    DuckData::Id color1;

    DuckData::Id color2;

    std::string error;

    ReplyMessage();

    explicit ReplyMessage(std::string error);

    explicit ReplyMessage(u8 connectedPlayers);

    ReplyMessage(u16 id, DuckData::Id color1, DuckData::Id color2);

    ReplyMessage(u16 id, u8 startGame, u8 connectedPlayers, DuckData::Id color1, DuckData::Id color2, std::string error);

    //Particular Instance to start game.
    static const ReplyMessage startGameInstance;

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
