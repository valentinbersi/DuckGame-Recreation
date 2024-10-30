
#include "ReceiveProtocol.h"

#include <vector>

#include <arpa/inet.h>

ReceiveProtocol::ReceiveProtocol(ActiveSocket& socket): skt(socket) {}

unsigned char ReceiveProtocol::recv_byte() {
    unsigned char byte;
    if (!skt.receive(&byte, sizeof(unsigned char))) {
        // throw;
    }
    return byte;
}

u16 ReceiveProtocol::recvShort() {
    u16 num;
    if (!skt.receive(&num, sizeof(u16))) {
        // throw
    }
    return ntohs(num);
}

u32 ReceiveProtocol::recvInt() {
    u32 num;
    if (!skt.receive(&num, sizeof(u32))) {
        // throw
    }
    return ntohl(num);
}

std::string ReceiveProtocol::recv_string() {
    uint16_t size = recvShort();
    std::vector<char> buffer(size);
    if (skt.receive(buffer.data(), size)) {
        // throw;
    }
    return std::string(buffer.begin(), buffer.end());
}
