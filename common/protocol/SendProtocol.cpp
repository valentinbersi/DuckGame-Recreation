#include "SendProtocol.h"

#include <arpa/inet.h>
#include "Types.h"


SendProtocol::SendProtocol(ActiveSocket& socket): skt(socket) {}

void SendProtocol::sendByte(unsigned char byte) {
    if (!skt.send(&byte, sizeof(char))) {
        // throw;
    }
}

void SendProtocol::sendShort(u16 num){
    u16 bigEndNum = htons(num);
    if(!skt.send(&bigEndNum, sizeof(uint16_t))){
        //throw
    }
}

void SendProtocol::sendInt(u32 num){
    u32 bigEndNum = htonl(num);
    if(!skt.send(&bigEndNum, sizeof(uint32_t))){
        //throw
    }
}

void SendProtocol::sendString(const std::string& string) {
    uint16_t size = string.size();
    size = htons(size);
    if (!skt.send(&size, sizeof(uint16_t))) {
        // throw;
    }

    if (!skt.send(string.c_str(), string.size())) {
        // throw;
    }
}


