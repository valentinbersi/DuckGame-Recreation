#pragma once
#include "Thread.h"
#include "ListenerSocket.h"
#include "VClient.h"
#include "GameMapMonitor.h"
#include "ThreadSafeHashMap.h"
#include "GameLoop.h"
#include <list>
#include <string>


class Acceptor: public Thread{
private:
    ListenerSocket acceptorSocket;
    GameMapMonitor& gamesMonitor;
    std::list<VirtualClient> clientes;
    bool removeIfNotConnected(VirtualClient& client);
    void reapDead();
public:
    Acceptor(const std::string& hostname,  GameMapMonitor& monitor);

    virtual void run() override;

    void stop() override; 

    ~Acceptor();
};
