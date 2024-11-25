#include "ActiveSocket.h"

#include <cerrno>
#include <stdexcept>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include "LibError.h"
#include "Resolver.h"
#include "StringUtils.h"

#define CONNECT_ERROR (-1)

#define NO_FLAGS 0

ActiveSocket::ActiveSocket(const int skt) {
    this->skt = skt;
    this->closed = false;
}

void ActiveSocket::chk_skt_or_fail() const {
    if (skt == INVALID_SOCKET) {
        throw std::runtime_error(SOCKET_FAIL);
    }
}

ActiveSocket::ActiveSocket(const cppstring hostname, const cppstring servname):
        skt(INVALID_SOCKET), closed(true) {
    Resolver resolver(hostname, servname, false);

    while (resolver.has_next()) {
        const addrinfo* addr = resolver.next();

        if (skt != INVALID_SOCKET)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == INVALID_SOCKET)
            continue;


        if (const int error = connect(skt, addr->ai_addr, addr->ai_addrlen); error == CONNECT_ERROR)
            continue;

        this->closed = false;
        return;
    }

    const int saved_errno = errno;

    if (skt != INVALID_SOCKET)
        ::close(skt);

    throw LibError(saved_errno, "socket construction failed (connect to %s:%s)",
                   hostname ? hostname : StringUtils::EMPTY_STRING,
                   servname ? servname : StringUtils::EMPTY_STRING);
}

ActiveSocket::ActiveSocket(ActiveSocket&& other) noexcept {
    this->skt = other.skt;
    this->closed = other.closed;

    other.skt = INVALID_SOCKET;
    other.closed = true;
}

ActiveSocket& ActiveSocket::operator=(ActiveSocket&& other) noexcept {
    if (this == &other)
        return *this;

    if (not this->closed) {
        ::shutdown(this->skt, static_cast<int>(ShutdownOptions::READ_WRITE));
        ::close(this->skt);
    }

    this->skt = other.skt;
    this->closed = other.closed;
    other.skt = INVALID_SOCKET;
    other.closed = true;

    return *this;
}

size_t ActiveSocket::receiveSome(const Buffer data, const size_t sz) const {
    chk_skt_or_fail();

    const ssize_t received = recv(this->skt, data, sz, NO_FLAGS);
    if (received == CLOSED)
        return CLOSED;

    if (received == RECEIVE_ERROR)
        throw LibError(errno, RECEIVE_FAIL);

    return received;
}

size_t ActiveSocket::sendSome(const ReadonlyBuffer data, const size_t sz) const {
    chk_skt_or_fail();

    const ssize_t sent = ::send(this->skt, data, sz, MSG_NOSIGNAL);

    if (sent == SEND_ERROR) {
        if (errno == EPIPE)
            return CLOSED;

        throw LibError(errno, SEND_FAIL);
    }

    return sent;
}

size_t ActiveSocket::receive(const Buffer data, const size_t sz) const {
    size_t received = 0;

    while (received < sz) {
        const size_t recv = receiveSome(static_cast<cstring>(data) + received, sz - received);

        if (recv == CLOSED) {
            if (received)
                throw LibError(EPIPE, "socket received only %d of %d bytes", received, sz);

            return CLOSED;
        }

        received += recv;
    }

    return sz;
}

size_t ActiveSocket::send(const ReadonlyBuffer data, const size_t sz) const {
    size_t sent = 0;

    while (sent < sz) {
        const size_t s = sendSome(static_cast<cppstring>(data) + sent, sz - sent);

        if (s == CLOSED) {
            if (sent)
                throw LibError(EPIPE, "socket sent only %d of %d bytes", sent, sz);

            return CLOSED;
        }

        sent += s;
    }

    return sent;
}

void ActiveSocket::shutdown(const ShutdownOptions how) const {
    chk_skt_or_fail();

    if (::shutdown(this->skt, static_cast<int>(how)) == SHUTDOWN_ERROR)
        throw LibError(errno, SHUTDOWN_FAIL);
}

int ActiveSocket::close() {
    chk_skt_or_fail();
    this->closed = true;
    return ::close(this->skt);
}

ActiveSocket::~ActiveSocket() {
    if (not this->closed) {
        ::shutdown(this->skt, static_cast<int>(ShutdownOptions::READ_WRITE));
        ::close(this->skt);
    }
}
