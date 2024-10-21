#pragma once

#include "ReceiveProtocol.h"
#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include <memory>

class ServerRecvProtocol: public ReceiveProtocol {
public:
    ServerRecvProtocol(ActiveSocket&);

    //  receiveMessage(); nose que va a devolver aun, no creo que arme el comando aca dentro sino en el receiver.

    ~ServerRecvProtocol() = default;
};