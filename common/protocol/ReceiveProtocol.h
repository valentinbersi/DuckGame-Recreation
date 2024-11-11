#pragma once
#include <string>

#include "ActiveSocket.h"
#include "ReceiverSocket.h"
#include "LibError.h"
#include "Types.h"
/**
 * Clase abstracta de uso para protocolo de recepcion de mensajes en servidor y cliente
 */
class ReceiveProtocol {
private:
    ReceiverSocket& skt;

protected:
    explicit ReceiveProtocol(ActiveSocket&);

    unsigned char recv_byte();

    u16 recvShort();

    u32 recvInt();

    std::string recv_string();

public:
    virtual ~ReceiveProtocol() {}
};
