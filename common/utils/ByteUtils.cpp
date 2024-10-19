#include "ByteUtils.h"

#include <climits>
#include <stdexcept>

#include "StringUtils.h"

unsigned char ByteUtils::parseUnsignedByte(const std::string& s) {

    if (!StringUtils::isNumberBetween(s, 0, UCHAR_MAX))
        throw std::runtime_error("String cannot be converted to unsigned byte");

    return std::stoul(s);
}
