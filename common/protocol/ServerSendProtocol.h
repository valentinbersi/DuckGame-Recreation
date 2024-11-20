#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "SendProtocol.h"
#include "Types.h"

// Forward declaration
struct ServerMessage;

/**
 *  Dedicated SendProtocol for the server
 */
class ServerSendProtocol final: public SendProtocol {

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<ServerMessage>&& mensaje);

    void sendLen(u16 len);

    void sendDuckData(const DuckData& objData);

    void sendVector2(const Vector2& vector);

    void sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers);

    ~ServerSendProtocol() = default;
};
