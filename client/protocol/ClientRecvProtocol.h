#pragma once
#include "../../common/protocol/ReceiveProtocol.h"
#include "../../common/socket/ActiveSocket.h"
#include "../../common/Types.h"
#include "../../common/game/GameStatus.hpp"
#include "../../common/game/DuckData.h"
#include "../../common/math/Math.h"

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
