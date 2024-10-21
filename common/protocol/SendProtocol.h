#pragma once
#include <string>

#include "ActiveSocket.h"
#include "SenderSocket.h"

class SendProtocol {
private:
    SenderSocket& skt;

protected:
    explicit SendProtocol(ActiveSocket& skt);

    void sendByte(unsigned char byte);

    void sendString(std::string& string);

public:
    virtual ~SendProtocol() {}
};
