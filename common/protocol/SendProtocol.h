#pragma once
#include <string>

#include "ActiveSocket.h"
#include "LibError.h"
#include "SenderSocket.h"
#include "Types.h"

/**
 * General Send Protocol
 */
class SendProtocol {
private:
    /**
     * Socket only able to send
     */
    SenderSocket& skt;

protected:
    /**
     * Construct a new Send Protocol object
     * @param skt the ActiveSocket to send data to
     */
    explicit SendProtocol(ActiveSocket& socket);

    /**
     * Send a byte through the socket
     * @param byte the byte to send
     */
    void sendByte(u8 byte);

    /**
     * Send 4 bytes through the socket
     * @param num the bytes to send
     */
    void sendInt(u32 num);

    /**
     * Send 2 bytes through the socket
     * @param num the bytes to send
     */
    void sendShort(u16 num);

    /**
     * Send a string through the socket
     * @param string the string to send
     */
    void sendString(const std::string& string);

public:
    /**
     * Defautl destructor
     */
    virtual ~SendProtocol() = default;
};
