#pragma once

#include "ActiveSocket.h"
#include "Types.h"

/**
 * Class that represents a listener socket (accepts connections).
 */
class ListenerSocket final: public Socket {
    int skt;
    bool closed;

    void chk_skt_or_fail() const;

public:
    ~ListenerSocket() override;

    ListenerSocket(const ListenerSocket&) = delete;
    ListenerSocket& operator=(const ListenerSocket&) = delete;
    ListenerSocket(ListenerSocket&&) noexcept = delete;
    ListenerSocket& operator=(ListenerSocket&&) noexcept = delete;


    /**
     * Construct a ListenerSocket from a service name.
     * @param servname the service name where the socket is going to listen
     * @throw LibError if the socket isn't able to listen
     */
    explicit ListenerSocket(cppstring servname);

    /**
     * Accept a new connection on the socket and return a socket for the new connection.
     * @return a socket for the new connection
     */
    [[nodiscard]] ActiveSocket accept() const;

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
