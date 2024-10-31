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

    std::unique_ptr<Message> recvGameStatus();

public:
    explicit ClientRecvProtocol(ActiveSocket& socket);

    std::unique_ptr<Message> receiveMessage();

    ~ClientRecvProtocol() = default;
};
