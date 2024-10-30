#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "GameObjectData.h"
#include "GameStatus.h"
#include "SendProtocol.h"
#include "Types.h"

class ServerSendProtocol: public SendProtocol {
private:
    HashMap<GameObjectID, std::function<void(const GameObjectData&)>> idsMap;

    void sendGameObject2DData(const GameObject2DData* obj2Data);

    void sendDuck(const GameObjectData& objData);

    void sendDuckData(const DuckData* objData);

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<GameStatus>& mensaje);

    ~ServerSendProtocol() = default;
};
