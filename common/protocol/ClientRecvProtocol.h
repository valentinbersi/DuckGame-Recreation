#pragma once
#include "ActiveSocket.h"
#include "DuckData.h"
#include "ServerMessage.h"
#include "GameStatus.h"
#include "Math.h"
#include "ReceiveProtocol.h"
#include "Types.h"

class ClientRecvProtocol: public ReceiveProtocol {
private:
    HashMap<GameObjectID, std::function<std::unique_ptr<GameObjectData>()>> idsMap;

    std::unique_ptr<GameObjectData> recvData();

    std::unique_ptr<GameObjectData> recvDuckData();

    std::unique_ptr<ServerMessage> recvGameStatus();

public:
    explicit ClientRecvProtocol(ActiveSocket& socket);

    std::unique_ptr<ServerMessage> receiveMessage();

    ~ClientRecvProtocol() = default;
};
