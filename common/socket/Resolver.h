#pragma once

#include <netdb.h>

#include "Types.h"

/**
 * Resolver class to resolve a hostname and service name to an address info
 */
class Resolver final {
    addrinfo* result;
    addrinfo* _next;

    /**
     * Check if the address info is valid, if not, throw an exception
     */
    void chk_addr_or_fail() const;

public:
    Resolver() = delete;
    Resolver(const Resolver&) = delete;
    Resolver& operator=(const Resolver&) = delete;

    Resolver(Resolver&&) noexcept;
    Resolver& operator=(Resolver&&) noexcept;
    ~Resolver();

    /**
     * Construct a new Resolver object
     * @param hostname The hostname to resolve
     * @param servname The service name to resolve
     * @param is_passive true if it must resolve to a passive socket, false otherwise
     */
    Resolver(cppstring hostname, cppstring servname, bool is_passive = false);

    /**
     * Construct a passive Resolver with a service name.
     * @param servname The service name to resolve
     */
    explicit Resolver(cppstring servname);

    /**
     * Check if there is a next address info
     * @return true if there's a next address info, false otherwise
     */
    [[nodiscard]] bool has_next() const;

    /**
     * Get the next address info
     * @return the next address info
     */
    const addrinfo* next();
};
