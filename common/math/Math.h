#pragma once

#include <algorithm>
#include <cmath>

class Math {
    constexpr static float CMP_EPSILON = 0.0001;

public:
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
     * Checks if a floating point number is less than another floating point number. The tolerance
     * of the comparison scales with the size of the numbers.
     * @param a The first number
     * @param b The second number
     * @return True if the first number is less than the second number, false otherwise
     */
    constexpr static bool isLessAprox(float a, float b) noexcept;

    /**
     * Checks if a floating point number is greater than another floating point number. The
     * @param a The first number
     * @param b The second number
     * @return True if the first number is greater than the second number, false otherwise
     */
    constexpr static bool isGreaterAprox(float a, float b) noexcept;

    /**
     * Checks if a floating point number is less than or equal to another floating point number. The
     * @param a The first number
     * @param b The second number
     * @return True if the first number is less than or equal to the second number, false otherwise
     */
    constexpr static bool isLessOrEqualAprox(float a, float b) noexcept;

    /**
     * Checks if a floating point number is greater than or equal to another floating point number.
     * The
     * @param a The first number
     * @param b The second number
     * @return True if the first number is greater than or equal to the second number, false
     * otherwise
     */
    constexpr static bool isGreaterOrEqualAprox(float a, float b) noexcept;

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
};

constexpr bool Math::isEqualAprox(const float a, const float b) noexcept {
    float tolerance = CMP_EPSILON * std::max(std::abs(a), std::abs(b));

    if (tolerance < CMP_EPSILON)
        tolerance = CMP_EPSILON;

    return isEqualAprox(a, b, tolerance);
}

constexpr bool Math::isEqualAprox(const float a, const float b, const float tolerance) noexcept {
    if (a == b)
        return true;

    return std::abs(a - b) < tolerance;
}

constexpr bool Math::isLessAprox(const float a, const float b) noexcept {
    return a < b && !isEqualAprox(a, b);
}

constexpr bool Math::isGreaterAprox(const float a, const float b) noexcept {
    return isLessAprox(b, a);
}

constexpr bool Math::isLessOrEqualAprox(const float a, const float b) noexcept {
    return a < b || isEqualAprox(a, b);
}

constexpr bool Math::isGreaterOrEqualAprox(const float a, const float b) noexcept {
    return isLessOrEqualAprox(b, a);
}

constexpr bool Math::isZeroAprox(const float a) noexcept { return std::abs(a) < CMP_EPSILON; }

constexpr float Math::toDegrees(const float angle) noexcept { return angle * 180.0f / M_PIf; }

constexpr float Math::toRadians(const float angle) noexcept { return angle * M_PIf / 180.0f; }
