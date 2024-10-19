#pragma once

#include <exception>

#include "Types.h"

/**
 * An exception representing an error in the resolver.\n
 * ResolverError from hands-on-sockets-in-cpp repository
 */
class ResolverError final: public std::exception {
    int gai_errno;

public:
    /**
     * Construct a ResolverError exception with the given gai_errno.
     * @param gai_errno The error code returned by getaddrinfo.
     */
    explicit ResolverError(int gai_errno);

    /**
     * @return a C-style character string describing the general cause of the current error.
     */
    [[nodiscard]] cppstring what() const noexcept override;

    ~ResolverError() override = default;
};
