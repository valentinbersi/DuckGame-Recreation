#pragma once

#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "ReceiveProtocol.h"

class ClientRecvProtocol: public ReceiveProtocol {
private: 
    std::unique_ptr<GameObjectData> recvData();

    std::unique_ptr<GameObjectData> recvPlayerData();
    
public:
    explicit ClientRecvProtocol(ActiveSocket& socket);

    GameStatus receiveMessage();

    ~ClientRecvProtocol() = default;
};
