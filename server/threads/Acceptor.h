#pragma once
#include "Thread.h"
#include "ListenerSocket.h"
#include "VClient.h"
#include "ThreadSafeHashMap.h"
#include "GameLoop.hpp"
#include <list>
#include <string>


class Acceptor: public Thread{
private:
    // ThreadSafeHashMap<>
    ListenerSocket acceptorSocket;
    std::list<VirtualClient> clientes;
    bool removeIfNotConnected(VirtualClient& client);
    void reapDead();
public:
    Acceptor(std::string& hostname);

    virtual void run() override;

    void stop() override; 

    ~Acceptor();
};
