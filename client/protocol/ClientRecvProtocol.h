#pragma once
#include "ReceiveProtocol.h"
#include "ActiveSocket.h"
#include "Types.h"
#include "GameStatus.h"
#include "DuckData.h"
#include "Math.h"

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
