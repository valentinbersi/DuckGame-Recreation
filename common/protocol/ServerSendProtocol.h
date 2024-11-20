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
    void sendGameObject2DData(const GameObject2DData* obj2Data);

    void sendDuckData(const DuckData* objData);

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<ServerMessage>&& mensaje);

    void sendLen(u16 len);

    // TODO: andrew fix this GameObjectData no longer exists
    // void sendDuck(const GameObjectData& objData);

    void sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers);

    ~ServerSendProtocol() = default;
};
