#pragma once
#include "ClientMessage.h"
#include "MessageType.h"

struct GameMessage: public ClientMessage {
public:
    InputAction action;

    u8 player; // 1 if player one, 2 if player two

    GameMessage(InputAction action, u8 twoPlayers);

    void send(ClientSendProtocol& clientProtocol) override;

    ~GameMessage();
};
