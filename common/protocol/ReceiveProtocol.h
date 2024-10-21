#pragma once
#include <string>

#include "ActiveSocket.h"
#include "ReceiverSocket.h"
/**
 * Clase abstracta de uso para protocolo de recepcion de mensajes en servidor y cliente
 */
class ReceiveProtocol {
private:
    ReceiverSocket& skt;

protected:
    explicit ReceiveProtocol(ActiveSocket&);

    unsigned char recv_byte();

    std::string recv_string();

    // Agregar los metodos virtuales para enviar y recibir mensajes.
};
