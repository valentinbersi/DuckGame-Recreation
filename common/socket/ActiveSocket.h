#pragma once

#include <cstddef>

#include "ReceiverSocket.h"
#include "SenderSocket.h"
#include "../Types.h"

/**
 * A class representing an ActiveSocket (sends and receives data).\n
 * Socket class from hands-on-sockets-in-cpp repository
 */
class ActiveSocket final: public ReceiverSocket, public SenderSocket {
    int skt;
    bool closed;

    /**
     * Construct a new ActiveSocket from a skt file descriptor.
     * @param skt the skt file descriptor.
     */
    explicit ActiveSocket(int skt);

    /**
     * Check if the socket is invalid and throw an exception if it is.
     * @throw LibError if the socket is invalid
     */
    void chk_skt_or_fail() const;

    friend class ListenerSocket;  // So it can create ActiveSockets with FDs

public:
    ActiveSocket() = delete;
    ActiveSocket(const ActiveSocket&) = delete;
    ActiveSocket& operator=(const ActiveSocket&) = delete;
    ActiveSocket(ActiveSocket&&) noexcept;
    ActiveSocket& operator=(ActiveSocket&&) noexcept;
    ~ActiveSocket() override;

    /**
     * Construct a ActiveSocket from a hostname and a service name.
     * @param hostname the host where the socket is going to connect
     * @param servname the service name where the socket is going to connect
     * @throw LibError if the socket isn't able to connect
     */
    ActiveSocket(cppstring hostname, cppstring servname);

    /**
     * Try to send sz bytes of data through the socket. Prone to short writes.
     * @param data the data to send
     * @param sz the size of the data
     * @return the number of bytes sent, @code CLOSED@endcode if the socket is closed
     * @throw LibError if the socket fails
     */
    std::size_t sendSome(ReadonlyBuffer data, std::size_t sz) const override;

    /**
     * Try to receive sz bytes of data through the socket. Prone to short reads.
     * @param data the buffer where the data is going to be stored
     * @param sz the size of the data to be received
     * @return the number of bytes received, @code CLOSED@endcode if the socket is closed
     * @throw LibError if the socket fails
     */
    std::size_t receiveSome(Buffer data, std::size_t sz) const override;

    /**
     * Send sz bytes of data through the socket. Blocks until all data is sent.
     * @param data the data to send
     * @param sz the size of the data
     * @return the number of bytes sent, @code CLOSED@endcode if the socket is closed
     * @throw LibError if the socket fails or is closed before all data is sent
     */
    size_t send(ReadonlyBuffer data, std::size_t sz) const override;

    /**
     * Receive sz bytes of data through the socket. Blocks until all data is received.
     * @param data the buffer where the data is going to be stored}
     * @param sz the size of the data to be received
     * @return the number of bytes received, @code CLOSED@endcode if the socket is closed
     * @throw LibError if the socket fails or is closed before all data is received
     */
    std::size_t receive(Buffer data, std::size_t sz) const override;

    /**
     * Shutdown the socket.
     * @param how the way to shutdown the socket
     */
    void shutdown(ShutdownOptions how) const override;

    /**
     * Close the socket.
     * @return Zero on success. On error, -1 is returned, and errno is set appropriately.
     */
    int close() override;
};
