#include "StringUtils.h"

#include <algorithm>
#include <sstream>
#include <utility>

std::vector<std::string> StringUtils::split(const std::string& s, const char delim) {
    std::vector<std::string> result;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delim)) result.push_back(std::move(token));

    return result;
}

bool StringUtils::isPositiveNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.cbegin(), str.cend(), isdigit);
}

bool StringUtils::isNumberBetween(const std::string& str, const size_t min, const size_t max) {
    return isPositiveNumber(str) && std::stoul(str) >= min && std::stoul(str) <= max;
}
