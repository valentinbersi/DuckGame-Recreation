#pragma once
#include <string>

#include "SenderSocket.h"
#include "ActiveSocket.h"

class SendProtocol{
private:
    SenderSocket& skt;

protected:
    SendProtocol(ActiveSocket& skt);

    void sendByte(unsigned char byte);

    void sendString(std::string string);

public:
    virtual ~SendProtocol() {}
};
