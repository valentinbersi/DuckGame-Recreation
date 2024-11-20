
#include "Acceptor.h"

#include <utility>

#include <syslog.h>

#include "LibError.h"

#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."
#define FORMAT "%s"
#define MAX_LOCAL_PLAYERS 2
#define ID_START_COUNT -1


Acceptor::Acceptor(const std::string& hostname, GameMapMonitor& monitor):
        acceptorSocket(hostname.c_str()), gamesMonitor(monitor), clientes() {}

bool Acceptor::removeIfNotConnected(VirtualClient& client) { return !client.isConnected(); }

void Acceptor::reapDead() {
    clientes.remove_if([this](VirtualClient& client) { return removeIfNotConnected(client); });
}

void Acceptor::run() noexcept {
    try {
        u16 clientID = ID_START_COUNT;
        while (_keep_running) {
            clientID += MAX_LOCAL_PLAYERS;
            ActiveSocket peer = acceptorSocket.accept();
            clientes.emplace_back(std::move(peer), gamesMonitor, clientID);
            reapDead();
        }
    } catch (const LibError& err) {
        if (is_alive()) {
            syslog(LOG_CRIT, FORMAT, err.what());
        }
        // LibError originated from stop() call. Expected when closing the server.
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    // Just to mantain consistency in the class status
    _keep_running = false;
    _is_alive = false;
}

void Acceptor::stop() {
    acceptorSocket.shutdown(Socket::ShutdownOptions::READ_WRITE);
    acceptorSocket.close();
    _keep_running = false;
    _is_alive = false;
}

Acceptor::~Acceptor() {}  // ALL RAII
