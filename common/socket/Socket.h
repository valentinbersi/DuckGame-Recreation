#pragma once
#include <sys/socket.h>

/**
 * Common interface for all sockets
 */
class Socket {
protected:
    static constexpr int INVALID_SOCKET = -1;

    static constexpr int SHUTDOWN_ERROR = -1;

    static constexpr auto SOCKET_FAIL =
            "socket with invalid file descriptor (-1), perhaps you are using a *previously moved* "
            "socket (and therefore invalid).";

    static constexpr auto SHUTDOWN_FAIL = "socket shutdown failed";

public:
    static constexpr char CLOSED = 0;

    virtual ~Socket() = default;

    enum class ShutdownOptions : unsigned char {
        READ = SHUT_RD,
        WRITE = SHUT_WR,
        READ_WRITE = SHUT_RDWR
    };

    /**
     * Shutdown the socket.
     * @param how the way to shutdown the socket
     */
    virtual void shutdown(ShutdownOptions how) const = 0;

    /**
     * Close the socket.
     * @return Zero on success. On error, -1 is returned, and errno is set appropriately.
     */
    virtual int close() = 0;
};
