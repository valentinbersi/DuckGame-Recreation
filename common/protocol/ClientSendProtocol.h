#pragma once
#include "ActiveSocket.h"
#include "Types.h"
#include "SendProtocol.h"

struct ClientMessage;

class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket& socket);

    void sendMessage(std::unique_ptr<ClientMessage> message);

    void sendLobbyMessage(u8 type, u8 request, u8 playerCount, std::string& player1Name, std::string& player2Name, u16 matchId);

    void sendGameMessage(u8 type, u8 action);

    ~ClientSendProtocol() override = default;
};
