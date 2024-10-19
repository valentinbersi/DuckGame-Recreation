#pragma once

#include <stdexcept>

#include "Types.h"

/**
 * An exception used to indicate a socket is closed
 */
class ClosedSocket final: public std::runtime_error {
public:
    explicit ClosedSocket(cppstring message);
};
