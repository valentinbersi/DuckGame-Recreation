#include "SendProtocol.h"
#include <arpa/inet.h>


SendProtocol::SendProtocol(ActiveSocket& socket): skt(socket){}

void SendProtocol::sendByte(unsigned char byte){
    if (!skt.send(&byte, sizeof(unsigned char))) {
        throw;
    }
}

void SendProtocol::sendString(std::string string){
    uint16_t size = string.size();
    size = htons(size);
    if (!skt.send(&size, sizeof(uint16_t))) {
        throw;
    }

    if (!skt.send(string.c_str(), string.size())) {
        throw;
    }
}
