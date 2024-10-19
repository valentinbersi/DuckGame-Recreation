#include "Resolver.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include "LibError.h"
#include "ResolverError.h"

#define DEFAULT_VALUE 0

#define NO_FLAGS 0

#define NO_ERROR 0

#define INVALID_ADDRESS_LIST                                                                      \
    "addresses list is invalid (null), perhaps you are using a *previously moved* resolver (and " \
    "therefore invalid)."

void Resolver::chk_addr_or_fail() const {
    if (result == nullptr)
        throw std::runtime_error(INVALID_ADDRESS_LIST);
}

Resolver::Resolver(Resolver&& other) noexcept {
    this->result = other.result;
    this->_next = other._next;

    other.result = nullptr;
    other._next = nullptr;
}

Resolver& Resolver::operator=(Resolver&& other) noexcept {
    if (this == &other)
        return *this;

    if (this->result)
        freeaddrinfo(this->result);

    this->result = other.result;
    this->_next = other._next;
    other.result = nullptr;
    other._next = nullptr;

    return *this;
}

Resolver::~Resolver() {
    if (this->result)
        freeaddrinfo(this->result);
}

Resolver::Resolver(const cppstring hostname, const cppstring servname, const bool is_passive) {
    addrinfo hints{};
    this->result = this->_next = nullptr;

    memset(&hints, DEFAULT_VALUE, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = is_passive ? AI_PASSIVE : NO_FLAGS;

    if (const int error = getaddrinfo(hostname, servname, &hints, &this->result);
        error != NO_ERROR) {

        if (error == EAI_SYSTEM)
            throw LibError(errno, "Name resolution failed for hostname '%s' y servname '%s'",
                           hostname ? hostname : "", servname ? servname : "");

        throw ResolverError(error);
    }

    this->_next = this->result;
}

Resolver::Resolver(const cppstring servname) {
    addrinfo hints{};
    this->result = this->_next = nullptr;

    memset(&hints, DEFAULT_VALUE, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (const int error = getaddrinfo(nullptr, servname, &hints, &this->result);
        error != NO_ERROR) {

        if (error == EAI_SYSTEM)
            throw LibError(errno, "Name resolution failed for hostname 'ANY' y servname '%s'",
                           servname ? servname : "");

        throw ResolverError(error);
    }

    this->_next = this->result;
}

bool Resolver::has_next() const {
    chk_addr_or_fail();
    return this->_next != nullptr;
}

const addrinfo* Resolver::next() {
    chk_addr_or_fail();
    const addrinfo* ret = this->_next;
    this->_next = ret->ai_next;
    return ret;
}
