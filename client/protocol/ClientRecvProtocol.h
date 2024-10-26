#pragma once

#include "ActiveSocket.h"
#include "ReceiveProtocol.h"
#include "Types.h"

class ClientRecvProtocol: public ReceiveProtocol {
private: 
    HashMap<GameObjectID, std::function<std::unique_ptr<GameObjectData>()>> idsMap;

    std::unique_ptr<GameObjectData> recvData();

    std::unique_ptr<GameObjectData> recvDuckData();
    
public:
    ClientRecvProtocol(ActiveSocket&);

    // Snapshot receiveMessage();

    ~ClientRecvProtocol() = default;

};
