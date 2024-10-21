
#include "ActiveSocket.h"
#include "ClientMessage.h"
#include "SendProtocol.h"

class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket&);

    void sendMessage(const ClientMessage& message);

    ~ClientSendProtocol() = default;
};
