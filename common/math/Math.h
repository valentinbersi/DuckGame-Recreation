#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>

#include "Types.h"

struct Math {
    constexpr static u16 EPSILON = 10000;
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

    /**
     * To sum up, it multiplies the float by a constant and converts it to an integer.
     * Its guaranteed that integerToFloat(floatToInteger(f)) == f.
     * @param f The float to convert
     * @return The converted integer
     */
    constexpr static unsigned int floatToInteger(float f);

    /**
     * To sum up, it multiplies the integer by a constant and converts it to a float.
     * Its guaranteed that integerToFloat(floatToInteger(i)) == i.
     * @param i The integer to convert
     * @return The converted float
     */
    constexpr static float integerToFloat(unsigned int i);

    /**
     * Solves a quadratic equation of the form ax^2 + bx + c = 0.
     * @param a The coefficient of x^2
     * @param b The coefficient of x
     * @param c The constant term
     * @return An array with the solutions to the equation
     */
    constexpr static std::array<float, 2> solveQuadratic(float a, float b, float c);
};

constexpr bool Math::isEqualAprox(const float a, const float b) noexcept {
    if (a == b)
        return true;
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

constexpr bool Math::isZeroAprox(const float a) noexcept { return std::abs(a) < INVERSE_EPSILON; }

constexpr float Math::toDegrees(const float angle) noexcept {
    return angle * 180.0f / std::numbers::pi_v<float>;
}

constexpr float Math::toRadians(const float angle) noexcept {
    return angle * std::numbers::pi_v<float> / 180.0f;
}

constexpr u32 Math::floatToInteger(const float f) { return static_cast<u32>(f * EPSILON); }

constexpr float Math::integerToFloat(const u32 i) {
    return static_cast<float>(i) * INVERSE_EPSILON;
}

constexpr std::array<float, 2> Math::solveQuadratic(const float a, const float b, const float c) {
    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return {NAN, NAN};

    if (discriminant == 0)
        return {-b / (2 * a), -b / (2 * a)};

    const float sqrtDiscriminant = std::sqrt(discriminant);
    return {(-b + sqrtDiscriminant) / (2 * a), (-b - sqrtDiscriminant) / (2 * a)};
}
