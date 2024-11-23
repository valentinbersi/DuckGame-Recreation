#pragma once
#include <list>
#include <string>

#include "GameLoop.h"
#include "GameMapMonitor.h"
#include "ListenerSocket.h"
#include "Thread.h"
#include "ThreadSafeHashMap.h"
#include "VClient.h"


class Acceptor: public Thread {
private:
    ListenerSocket acceptorSocket;
    GameMapMonitor& gamesMonitor;
    std::list<VirtualClient> clientes;
    bool removeIfNotConnected(VirtualClient& client);
    void reapDead();

public:
    /**
     * Create a new Acceptor
     * @param hostname The hostname to accept connections from
     * @param monitor The monitor tgat will be used by te clients
     */
    Acceptor(const std::string& hostname, GameMapMonitor& monitor);

    /**
     * Accept connections and remove disconnected Clients
     */
    void run() noexcept override;

    /**
     * Stop the acceptor
     */
    void stop() override;

    /**
     * Destroy the acceptor
     */
    ~Acceptor();
};
