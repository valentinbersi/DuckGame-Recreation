#pragma once
#include <string>

#include "Acceptor.h"
#include "GameMapMonitor.h"

class Server {
private:
    GameMapMonitor gameMap;
    Acceptor acceptor;
    std::string readInput();

public:
    Server(const std::string& hostname);

    int run() noexcept;

    ~Server();
};
