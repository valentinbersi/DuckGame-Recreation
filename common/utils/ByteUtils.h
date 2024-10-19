#pragma once

#include <string>

/**
 * A class that contains utility functions for working with bytes
 */
class ByteUtils final {
public:
    /**
     * Parse the given string into an unsigned byte
     * @param s The string to parse. Must be in base 10
     * @return The unsigned byte
     */
    static unsigned char parseUnsignedByte(const std::string& s);
};
