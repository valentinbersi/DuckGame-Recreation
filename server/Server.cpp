
#include "Server.h"

#include <iostream>

#define CLOSE_SERVER "q"

Server::Server(const std::string& hostname): gameMap(), acceptor(hostname, gameMap) {}

std::string Server::readInput() {
    std::string input;
    std::cin >> input;
    return input;
}

int Server::run() noexcept {
    acceptor.start();
    while (readInput() != CLOSE_SERVER) {
        continue;
    }
    return EXIT_SUCCESS;
}

Server::~Server() {
    acceptor.stop();
    acceptor.join();
}
