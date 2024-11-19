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
    Acceptor(const std::string& hostname, GameMapMonitor& monitor);

    void run() noexcept override;

    void stop() override;

    ~Acceptor();
};
