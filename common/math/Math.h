#pragma once

#include <algorithm>
#include <cmath>

#include "../Types.h"

struct Math {
    constexpr static u32 EPSILON = 10000;
    constexpr static float INVERSE_EPSILON = 1.f / EPSILON;

    /**
     * Checks if two floating point numbers are approximately equal. The tolerance of the
     * comparison scales with the size of the numbers.
     * @param a The first number
     * @param b The second number
     * @return True if the numbers are approximately equal, false otherwise
     */
    constexpr static bool isEqualAprox(float a, float b) noexcept;

    /**
     * Checks if two floating point numbers are approximately equal.
     * @param a The first number
     * @param b The second number
     * @param tolerance The tolerance of the comparison
     * @return True if the numbers are approximately equal, false otherwise
     */
    constexpr static bool isEqualAprox(float a, float b, float tolerance) noexcept;

    /**
     * Checks if a floating point number is approximately zero. Is faster than isEqualAprox(a, 0).
     * @param a The number to check
     * @return True if the number is approximately zero, false otherwise
     */
    constexpr static bool isZeroAprox(float a) noexcept;

    /**
     * Converts an angle in radians to degrees.
     * @param angle The angle in radians
     * @return The angle in degrees
     */
    constexpr static float toDegrees(float angle) noexcept;

    /**
     * Converts an angle in degrees to radians.
     * @param angle The angle in degrees
     * @return The angle in radians
     */
    constexpr static float toRadians(float angle) noexcept;

    /**
     * To sum up, it multiplies the float by a constant and converts it to an integer.
     * Its guaranteed that integerToFloat(floatToInteger(f)) == f.
     * @param f The float to convert
     * @return The converted integer
     */
    constexpr static u32 floatToInteger(float f);

    /**
     * To sum up, it multiplies the integer by a constant and converts it to a float.
     * Its guaranteed that integerToFloat(floatToInteger(i)) == i.
     * @param i The integer to convert
     * @return The converted float
     */
    constexpr static float integerToFloat(u32 i);
};

constexpr bool Math::isEqualAprox(const float a, const float b) noexcept {
    float tolerance = INVERSE_EPSILON * std::max(std::abs(a), std::abs(b));

    if (tolerance < INVERSE_EPSILON)
        tolerance = INVERSE_EPSILON;

    return isEqualAprox(a, b, tolerance);
}

constexpr bool Math::isEqualAprox(const float a, const float b, const float tolerance) noexcept {
    if (a == b)
        return true;

    return std::abs(a - b) < tolerance;
}

constexpr bool Math::isZeroAprox(const float a) noexcept { return std::abs(a) < INVERSE_EPSILON; }

constexpr float Math::toDegrees(const float angle) noexcept { return angle * 180.0f / M_PIf; }

constexpr float Math::toRadians(const float angle) noexcept { return angle * M_PIf / 180.0f; }

constexpr u32 Math::floatToInteger(const float f) { return static_cast<u32>(f * EPSILON); }

constexpr float Math::integerToFloat(const u32 i) {
    return static_cast<float>(i) * INVERSE_EPSILON;
}
