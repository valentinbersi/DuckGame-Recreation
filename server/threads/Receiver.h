
#include "Thread.h"
#include "ServerRecvProtocol.h"
#include "BlockingQueue.h"
#include "Command.h"
#include <memory>

class Receiver: public Thread{
private:
    ServerRecvProtocol protocol;
    // CommnadFactory factory;
public:
    Receiver(ActiveSocket& socket);

    virtual void run() override;

    void stop() override;

    ~Receiver();
};


