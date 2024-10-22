
#include "ReceiveProtocol.h"

#include <vector>

#include <arpa/inet.h>

ReceiveProtocol::ReceiveProtocol(ActiveSocket& socket): skt(socket) {}

unsigned char ReceiveProtocol::recv_byte() {
    unsigned char byte;
    size_t recv = skt.receive(&byte, sizeof(unsigned char));
    if (!recv) {
        // throw;
    }
    return byte;
}

std::string ReceiveProtocol::recv_string() {
    uint16_t size;
    if (!skt.receive(&size, sizeof(uint16_t))) {
        // throw;
    }

    size = ntohs(size);
    std::vector<char> buffer(size);
    if (skt.receive(buffer.data(), size)) {
        // throw;
    }

    return std::string(buffer.begin(), buffer.end());
}
