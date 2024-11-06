#pragma once
#include <string>

#include "ClientMessage.h"
#include "Types.h"

struct LobbyMessage: public ClientMessage {
public:
    LobbyRequest request;
    u8 playerCount;
    std::string player1Name;
    std::string player2Name;
    u16 matchId;

    LobbyMessage();

    LobbyMessage(LobbyRequest request, u8 count, std::string name1, std::string name2, u16 id);

    void send(ClientSendProtocol& clientProtocol) override;

    ~LobbyMessage();
};