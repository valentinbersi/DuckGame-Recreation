#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "SendProtocol.h"
#include "Types.h"

struct ServerMessage;

class ServerSendProtocol: public SendProtocol {
private:
    HashMap<GameObjectID, std::function<void(const GameObjectData&)>> idsMap;

    void sendGameObject2DData(const GameObject2DData* obj2Data);

    void sendDuckData(const DuckData* objData);

    // void sendResponse();

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<ServerMessage>&& mensaje);

    void sendDuck(const GameObjectData& objData);

    void sendReplyMessage(u16 matchID, u8 startGame);

    ~ServerSendProtocol() = default;
};
