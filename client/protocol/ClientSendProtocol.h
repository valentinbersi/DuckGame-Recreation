
#include "SendProtocol.h"
#include "ClientMessage.h"
#include "ActiveSocket.h"

class ClientSendProtocol: public SendProtocol{
public:
    ClientSendProtocol(ActiveSocket&);

    void sendMessage(const ClientMessage& message);

    ClientSendProtocol() = default;
};
