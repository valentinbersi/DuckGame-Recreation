#pragma once
#include "Thread.h"
#include "ListenerSocket.h"
#include "VClient.h"
#include <list>
#include <string>


class Acceptor: public Thread{
private:
    //voy a necesitar el map para darselo a los clientes.
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
