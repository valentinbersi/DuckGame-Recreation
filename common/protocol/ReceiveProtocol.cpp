
#include "ReceiveProtocol.h"

#include <vector>

#include <arpa/inet.h>

#define ERR_RECEIVE "could not receive message"

ReceiveProtocol::ReceiveProtocol(ActiveSocket& socket): skt(socket) {}

u8 ReceiveProtocol::recvByte() {
    u8 byte;
    if (!skt.receive(&byte, sizeof(u8))) {
        throw LibError(EPIPE, ERR_RECEIVE);
    }
    return byte;
}

u16 ReceiveProtocol::recvShort() {
    u16 num;
    if (!skt.receive(&num, sizeof(u16))) {
        throw LibError(EPIPE, ERR_RECEIVE);
    }
    return ntohs(num);
}

u32 ReceiveProtocol::recvInt() {
    u32 num;
    if (!skt.receive(&num, sizeof(u32))) {
        throw LibError(EPIPE, ERR_RECEIVE);
    }
    return ntohl(num);
}

std::string ReceiveProtocol::recvString() {
    uint16_t size = recvShort();
    std::vector<char> buffer(size);
    if (!skt.receive(buffer.data(), size)) {
        throw LibError(EPIPE, ERR_RECEIVE);
    }
    return std::string(buffer.begin(), buffer.end());
}
