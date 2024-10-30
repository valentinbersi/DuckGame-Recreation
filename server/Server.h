#pragma once
#include "GameMapMonitor.h"
#include "Acceptor.h"
#include <string>

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
