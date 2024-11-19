#pragma once
#include <string>

#include "ActiveSocket.h"
#include "ReceiverSocket.h"
#include "LibError.h"
#include "Types.h"
/**
 * General Receive Protocol
 */
class ReceiveProtocol {
private:
    /**
     * Socket only able to receive
     */
    ReceiverSocket& skt;

protected:
    /**
     * Construct a new Receive Protocol object
     * @param skt the ReceiverSocket to receive data from
     */
    explicit ReceiveProtocol(ActiveSocket& socket);

    /**
     * Receive a byte from the socket
     * @return the byte received
     */
    u8 recvByte();

    /**
     * Receive 2 bytes from the socket
     * @return the bytes received
     */
    u16 recvShort();

    /**
     * Receive 4 bytes from the socket
     * @return the bytes received
     */
    u32 recvInt();

    /**
     * Receive a string from the socket
     * @return the string received
     */
    std::string recv_string();

public:
    /**
     * Defautl destructor
     */
    virtual ~ReceiveProtocol() = default;
};
