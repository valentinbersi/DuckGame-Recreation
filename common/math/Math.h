#pragma once

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

constexpr bool Math::isZeroAprox(const float a) noexcept { return std::abs(a) < CMP_EPSILON; }

constexpr float Math::toDegrees(const float angle) noexcept { return angle * 180.0f / M_PIf; }

constexpr float Math::toRadians(const float angle) noexcept { return angle * M_PIf / 180.0f; }
