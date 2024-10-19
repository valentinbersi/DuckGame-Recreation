#include "ListenerSocket.h"

#include <cerrno>
#include <stdexcept>

#include <unistd.h>

#include "ClosedSocket.h"
#include "LibError.h"
#include "Resolver.h"
#include "StringUtils.h"

#define SOCKET_OPTION_ERROR (-1)
#define BIND_ERROR (-1)
#define LISTEN_ERROR (-1)

#define CONNECTION_QUEUE_MAX_SIZE 20

#define ACCEPT_FAIL "socket accept failed"

#define CLOSED_MESSAGE "socket is closed"

void ListenerSocket::chk_skt_or_fail() const {
    if (skt == INVALID_SOCKET) {
        throw std::runtime_error(SOCKET_FAIL);
    }
}

ListenerSocket::~ListenerSocket() {
    if (not this->closed) {
        ::shutdown(this->skt, static_cast<int>(ShutdownOptions::READ_WRITE));
        ::close(this->skt);
    }
}

ListenerSocket::ListenerSocket(const cppstring servname) {
    Resolver resolver(nullptr, servname, true);

    int skt = INVALID_SOCKET;
    this->closed = true;
    while (resolver.has_next()) {
        const addrinfo* addr = resolver.next();

        if (skt != INVALID_SOCKET)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == INVALID_SOCKET)
            continue;


        int optval = 1;
        int error = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (error == SOCKET_OPTION_ERROR)
            continue;


        error = bind(skt, addr->ai_addr, addr->ai_addrlen);
        if (error == BIND_ERROR)
            continue;


        error = listen(skt, CONNECTION_QUEUE_MAX_SIZE);
        if (error == LISTEN_ERROR)
            continue;

        this->closed = false;
        this->skt = skt;
        return;
    }

    const int saved_errno = errno;

    if (skt != INVALID_SOCKET)
        ::close(skt);

    throw LibError(saved_errno, "socket construction failed (listen on %s)",
                   servname ? servname : StringUtils::EMPTY_STRING);
}

ActiveSocket ListenerSocket::accept() const {
    chk_skt_or_fail();

    const int peer_skt = ::accept(this->skt, nullptr, nullptr);
    if (peer_skt == INVALID_SOCKET)
        throw ClosedSocket(CLOSED_MESSAGE);

    return ActiveSocket(peer_skt);
}

void ListenerSocket::shutdown(ShutdownOptions how) const {
    chk_skt_or_fail();

    if (::shutdown(this->skt, static_cast<int>(how)) == SHUTDOWN_ERROR)
        throw LibError(errno, SHUTDOWN_FAIL);
}

int ListenerSocket::close() {
    chk_skt_or_fail();
    this->closed = true;
    return ::close(this->skt);
}
