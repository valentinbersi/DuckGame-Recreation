#pragma once
#include "ClientMessage.h"
#include "MessageType.h"

struct GameMessage: public ClientMessage {
public:
    InputAction action;

    GameMessage(InputAction action);

    void send(ClientSendProtocol& clientProtocol) override;
    
    ~GameMessage();
};
