#include "SendProtocol.h"

#include <arpa/inet.h>

#define ERR_SEND "could not send message"


SendProtocol::SendProtocol(ActiveSocket& socket): skt(socket) {}

void SendProtocol::sendByte(u8 byte) {
    if (!skt.send(&byte, sizeof(u8))) {
        throw LibError(EPIPE, ERR_SEND);
    }
}

void SendProtocol::sendShort(u16 num) {
    u16 bigEndNum = htons(num);
    if (!skt.send(&bigEndNum, sizeof(u16))) {
        throw LibError(EPIPE, ERR_SEND);
    }
}

void SendProtocol::sendInt(u32 num) {
    u32 bigEndNum = htonl(num);
    if (!skt.send(&bigEndNum, sizeof(u32))) {
        throw LibError(EPIPE, ERR_SEND);
    }
}

void SendProtocol::sendString(const std::string& string) {
    sendShort(string.size());
    if (!skt.send(string.c_str(), string.size())) {
        throw LibError(EPIPE, ERR_SEND);
    }
}
