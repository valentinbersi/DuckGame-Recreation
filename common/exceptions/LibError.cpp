#undef _GNU_SOURCE
#undef GNU_SOURCE

#define INTERROGATION_MARK '?'
#define SPACE ' '
#define STRING_END '\0'

#define ERROR 0

#define UKNOWN_ERROR_SIZE 4

#include "LibError.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

LibError::LibError(const int error_code, const cppstring fmt, ...) noexcept: msg_error() {
    va_list args;
    va_start(args, fmt);

    int size = vsnprintf(msg_error, sizeof(msg_error), fmt, args);

    va_end(args);

    if (size < ERROR) {
        msg_error[0] = msg_error[1] = msg_error[2] = INTERROGATION_MARK;
        msg_error[3] = SPACE;
        msg_error[4] = STRING_END;

        size = UKNOWN_ERROR_SIZE;
    }

    strerror_r(error_code, msg_error + size, sizeof(msg_error) - size);

    msg_error[sizeof(msg_error) - 1] = STRING_END;
}

cppstring LibError::what() const noexcept { return msg_error; }
