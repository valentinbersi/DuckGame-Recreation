#pragma once

#include <string>
#include <vector>

struct StringUtils {
    static constexpr auto EMPTY_STRING = "";

    StringUtils() = delete;
    StringUtils(const StringUtils&) = delete;
    StringUtils& operator=(const StringUtils&) = delete;
    StringUtils(StringUtils&&) = delete;
    StringUtils& operator=(StringUtils&&) = delete;
    ~StringUtils() = delete;

    /**
     * Splits a string by a delimiter
     * @param s The string to split
     * @param delim The delimiter to split the string by
     * @return A vector with the split strings
     */
    static std::vector<std::string> split(const std::string& s, char delim);

    /**
     * Checks if a string is a positive number
     * @param str The string to check. Must be in base 10
     * @return True if the string is numeric, false otherwise
     */
    static bool isPositiveNumber(const std::string& str);

    /**
     * Checks if a numeric string is in the [min, max] interval
     * @param str the str representing the number. Must be in base 10
     * @param min the min value of the interval
     * @param max the max value of the interval
     * @return true if the string is in the interval, false otherwise
     */
    static bool isNumberBetween(const std::string& str, size_t min, size_t max);
};
