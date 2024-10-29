#pragma once

#include <cstddef>

#include "Socket.h"
#include "../Types.h"

/**
 * Interface for a sender socket (a socket that only sends data)
 */
class SenderSocket: public Socket {
protected:
    static constexpr int SEND_ERROR = -1;

    static constexpr auto SEND_FAIL = "socket send failed";

public:
    /**
     * Try to send sz bytes of data through the socket. Prone to short writes.
     * @param data the data to send
     * @param sz the size of the data
     * @return the number of bytes sent, @code CLOSED@endcode if the socket is closed
     */
    virtual std::size_t sendSome(ReadonlyBuffer data, std::size_t sz) const = 0;

    /**
     * Send sz bytes of data through the socket. Blocks until all data is sent.
     * @param data the data to send
     * @param sz the size of the data
     * @return the number of bytes sent, @code CLOSED@endcode if the socket is closed
     */
    virtual std::size_t send(ReadonlyBuffer data, std::size_t sz) const = 0;
};
