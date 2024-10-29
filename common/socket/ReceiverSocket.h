#pragma once

#include <cstddef>

#include "Socket.h"
#include "../Types.h"

/**
 * Interface for a receiver socket (a socket that only receives data)
 */
class ReceiverSocket: public Socket {
protected:
    static constexpr int RECEIVE_ERROR = -1;

    static constexpr auto RECEIVE_FAIL = "socket receive failed";

public:
    /**
     * Try to receive sz bytes of data through the socket. Prone to short reads.
     * @param data the buffer where the data is going to be stored
     * @param sz the size of the data to be received
     * @return the number of bytes received, @code CLOSED@endcode if the socket is closed
     */
    virtual std::size_t receiveSome(Buffer data, std::size_t sz) const = 0;

    /**
     * Send sz bytes of data through the socket. Blocks until all data is sent.
     * @param data the data to send
     * @param sz the size of the data
     * @return the number of bytes sent, @code CLOSED@endcode if the socket is closed
     */
    virtual std::size_t receive(Buffer data, std::size_t sz) const = 0;
};
