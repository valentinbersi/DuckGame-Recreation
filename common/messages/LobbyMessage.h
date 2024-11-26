#pragma once
#include <string>

#include "ClientMessage.h"
#include "DuckData.h"
#include "Types.h"

struct LobbyMessage: public ClientMessage {
public:
    LobbyRequest request;
    u8 playerCount;
    u16 matchId;
    DuckData::Id color;

    LobbyMessage();

    LobbyMessage(LobbyRequest request, u8 count, u16 id, DuckData::Id color);

    void send(ClientSendProtocol& clientProtocol) override;

    bool operator==(const LobbyMessage& other) const;

    ~LobbyMessage();
};
