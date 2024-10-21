#pragma once
#include <string>

#include "SenderSocket.h"
#include "ActiveSocket.h"

class SendProtocol{
private:
    SenderSocket& skt;

public:
    SendProtocol(ActiveSocket& skt);

    void send_byte(unsigned char byte);

    void send_string(std::string string);
};
