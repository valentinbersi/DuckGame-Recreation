#pragma once
#include <string>
#include <vector>

#include "Acceptor.h"
#include "GameMapMonitor.h"

class Server {
private:
    GameMapMonitor gameMap;
    Acceptor acceptor;
    std::string readInput();

public:
    /**
     * Create a new Server object
     * @param hostname The hostname to listen to
     */
    explicit Server(const std::string& hostname);

    /**
     * Run the server
     * @return 0 if the server ran successfully, 1 otherwise
     */
    int run() noexcept;

    /**
     * Destroy the Server
     */
    ~Server();
};
