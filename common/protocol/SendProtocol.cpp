#include "SendProtocol.h"

#include <arpa/inet.h>
#include "Types.h"


SendProtocol::SendProtocol(ActiveSocket& socket): skt(socket) {}

void SendProtocol::sendByte(unsigned char byte) {
    if (!skt.send(&byte, sizeof(unsigned char))) {
        // throw;
    }
}

void SendProtocol::sendShort(u16 num){
    u16 bigEndNum = htons(num);
    if(!skt.send(&bigEndNum, sizeof(u16))){
        //throw
    }
}

void SendProtocol::sendInt(u32 num){
    u32 bigEndNum = htonl(num);
    if(!skt.send(&bigEndNum, sizeof(u32))){
        //throw
    }
}

void SendProtocol::sendString(std::string& string) {
    sendShort(string.size());
    if (!skt.send(string.c_str(), string.size())) {
        // throw;
    }
}


