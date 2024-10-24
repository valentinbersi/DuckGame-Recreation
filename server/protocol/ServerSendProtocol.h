#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "SendProtocol.h"
#include <vector>

class ServerSendProtocol: public SendProtocol {
private:
    void sendData(std::vector<char>& data);

    void sendPlayerData(std::vector<char>& playerData);

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<GameStatus>& mensaje);

    ~ServerSendProtocol() = default;
};
