#pragma once

#include <exception>

#include "../Types.h"

/**
 * An exception that represents a c-stdlib error.\n
 * LibError class from hands-on-sockets-in-cpp repository.
 */
class LibError final: public std::exception {
    static constexpr size_t MAX_MSG_SIZE = 256;

    char msg_error[MAX_MSG_SIZE];

public:
    /**
     * Construct a LibError exception with a formatted message.
     * @param error_code the errno value
     * @param fmt the format string
     * @param ... the arguments for the format string
     */
    LibError(int error_code, cppstring fmt, ...) noexcept;

    /**
     * @return a C-style character string describing the general cause of the current error.
     */
    [[nodiscard]] cppstring what() const noexcept override;

    ~LibError() override = default;
};
