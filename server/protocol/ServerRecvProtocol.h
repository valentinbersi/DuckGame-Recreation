#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "ReceiveProtocol.h"

class ServerRecvProtocol: public ReceiveProtocol {
public:
    explicit ServerRecvProtocol(ActiveSocket&);

    //  receiveMessage(); nose que va a devolver aun, no creo que arme el comando aca dentro sino en
    //  el receiver.

    ~ServerRecvProtocol() = default;
};
