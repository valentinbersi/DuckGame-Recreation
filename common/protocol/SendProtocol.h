#pragma once
#include <string>

#include "ActiveSocket.h"
#include "SenderSocket.h"
#include "Types.h"


class SendProtocol {
private:
    SenderSocket& skt;

protected:
    explicit SendProtocol(ActiveSocket& skt);

    void sendByte(unsigned char byte);

    void sendInt(u32 num);

    void sendShort(u16 num);
    
    void sendString(const std::string& string);

public:
    virtual ~SendProtocol() {}
};
