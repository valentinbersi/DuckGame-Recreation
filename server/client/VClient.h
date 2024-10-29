#pragma once
#include "Receiver.h"
#include "Sender.h"
#include "BlockingQueue.h"
#include "Command.h"
#include <memory>
#include "ActiveSocket.h"

class VirtualClient{
private:
    ActiveSocket skt;
    //mapa de gameloops va aqui, referencia
    BlockingQueue<std::unique_ptr<Command>>* gameQueue; //No tengo de otra porque aun no se cual es
    BlockingQueue<std::shared_ptr<GameStatus>> sendQueue; 
    Receiver receiver; //necesario?
    Sender sender;

public:
    VirtualClient(ActiveSocket&& socket);

    bool isConnected();

    ~VirtualClient();

};
