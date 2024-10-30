#pragma once
#include "ActiveSocket.h"
#include "DuckData.h"
#include "GameStatus.h"
#include "Math.h"
#include "ReceiveProtocol.h"
#include "Types.h"

class ClientRecvProtocol: public ReceiveProtocol {
private:
    HashMap<GameObjectID, std::function<std::unique_ptr<GameObjectData>()>> idsMap;

    std::unique_ptr<GameObjectData> recvData();

    std::unique_ptr<GameObjectData> recvDuckData();

public:
    explicit ClientRecvProtocol(ActiveSocket& socket);

    GameStatus receiveMessage();

    ~ClientRecvProtocol() = default;
};
