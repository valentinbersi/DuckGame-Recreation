#include "Vector2.h"

#include <cmath>
#include <stdexcept>

#include "Math.h"

#define DEFAULT_VALUE 0

#define ANGLE "Vector2::angle()"
#define ANGLE_RESPECT_TO "Vector2::angle(const Vector2&)"
#define BOUNCE "Vector2::bounce(const Vector2&)"
#define DIRECTION_TO "Vector2::directionTo(const Vector2&)"
#define NORMALIZED "Vector2::normalized()"
#define PROJECT "Vector2::normalized()"
#define REFLECT "Vector2::reflect(const Vector2&)"

#define UNDEFINED_FOR_ZERO " is undefined for (0, 0) vector"
#define UNDEFINED_FOR_ZERO_V " is undefined for (0, 0) v argument"
#define UNDEFINED_FOR_ZERO_NORMAL " is undefined for (0, 0) normal argument"

#define DIVISION_BY_ZERO "Vector2::operator/(real) is undefined for 0 scalar"

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::UP(0, -1);
const Vector2 Vector2::DOWN(0, 1);
const Vector2 Vector2::LEFT(-1, 0);
const Vector2 Vector2::RIGHT(1, 0);

Vector2::Vector2() noexcept: _x(DEFAULT_VALUE), _y(DEFAULT_VALUE) {}

Vector2::Vector2(const Vector2& other) noexcept = default;

Vector2& Vector2::operator=(const Vector2& other) noexcept = default;

Vector2::Vector2(Vector2&& other) noexcept: _x(other._x), _y(other._y) {
    other._x = 0;
    other._y = 0;
}

Vector2& Vector2::operator=(Vector2&& other) noexcept {
    _x = other._x;
    _y = other._y;
    other._x = 0;
    other._y = 0;
    return *this;
}

Vector2::~Vector2() noexcept = default;

Vector2::Vector2(const float x, const float y) noexcept: _x(x), _y(y) {}

Vector2::Vector2(const float angle) noexcept: Vector2(std::cos(angle), std::sin(angle)) {}

float Vector2::angle() const {
    if (isZero())
        throw std::logic_error(ANGLE UNDEFINED_FOR_ZERO);

    return std::atan2(_y, _x);
}

float Vector2::angle(const Vector2& v) const {
    if (isZero())
        throw std::logic_error(ANGLE_RESPECT_TO UNDEFINED_FOR_ZERO);

    if (v.isZero())
        throw std::invalid_argument(ANGLE_RESPECT_TO UNDEFINED_FOR_ZERO_V);

    return std::acos(cross(v) / dot(v));
}

Vector2 Vector2::bounce(const Vector2& normal) const try {
    return -reflect(normal);
} catch ([[maybe_unused]] const std::logic_error& e) {
    throw std::logic_error(BOUNCE UNDEFINED_FOR_ZERO);
}

float Vector2::cross(const Vector2& v) const noexcept { return _x * v._y - _y * v._x; }

Vector2 Vector2::directionTo(const Vector2& v) const {
    const Vector2 result = v - *this;

    try {
        return result.normalized();
    } catch ([[maybe_unused]] const std::logic_error& e) {
        throw std::logic_error(DIRECTION_TO UNDEFINED_FOR_ZERO);
    }
}

float Vector2::distance(const Vector2& v) const { return (*this - v).length(); }

float Vector2::dot(const Vector2& v) const noexcept { return _x * v._x + _y * v._y; }

bool Vector2::operator==(const Vector2& v) const noexcept {
    return Math::isEqualAprox(_x, v._x) && Math::isEqualAprox(_y, v._y);
}

bool Vector2::operator!=(const Vector2& v) const noexcept { return !(*this == v); }

bool Vector2::isNormalized() const noexcept { return Math::isEqualAprox(lengthSquared(), 1); }

bool Vector2::isZero() const noexcept { return Math::isZeroAprox(_x) && Math::isZeroAprox(_y); }

float Vector2::length() const noexcept {
    if (isZero())
        return 0;

    return std::hypot(_x, _y);
}

float Vector2::lengthSquared() const noexcept {
    if (isZero())
        return 0;

    return _x * _x + _y * _y;
}

Vector2 Vector2::normalized() const {
    if (isZero())
        throw std::logic_error(NORMALIZED UNDEFINED_FOR_ZERO);

    return *this / length();
}

Vector2 Vector2::orthogonal() const { return {_y, -_x}; }

Vector2 Vector2::project(const Vector2& v) const {
    if (v.isZero())
        throw std::logic_error(PROJECT UNDEFINED_FOR_ZERO_V);

    if (isZero())
        return ZERO;

    return (dot(v) / v.lengthSquared()) * v;
}

Vector2 Vector2::reflect(const Vector2& normal) const {
    if (normal.isZero())
        throw std::logic_error(REFLECT UNDEFINED_FOR_ZERO_NORMAL);

    return 2.0f * dot(normal) * normal - *this;
}

Vector2 Vector2::rotated(const float angle) const {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);
    return {_x * cos + _y * sin, _x * sin - _y * cos};
}

Vector2 Vector2::operator*(const float scalar) const { return {scalar * _x, scalar * _y}; }

Vector2& Vector2::operator*=(const float scalar) { return *this = *this * scalar; }

Vector2 Vector2::operator+(const Vector2& v) const { return {v._x + _x, v._y + _y}; }

Vector2& Vector2::operator+=(const Vector2& v) { return *this = *this + v; }

Vector2 Vector2::operator-(const Vector2& v) const { return {v._x - _x, v._y - _y}; }

Vector2& Vector2::operator-=(const Vector2& v) { return *this = *this - v; }

Vector2 Vector2::operator/(const float scalar) const {
    if (Math::isZeroAprox(scalar))
        throw std::logic_error(DIVISION_BY_ZERO);

    return {scalar / _x, scalar / _y};
}

Vector2& Vector2::operator/=(const float scalar) { return *this = *this / scalar; }

const Vector2& Vector2::operator+() const { return *this; }

Vector2 Vector2::operator-() const { return {-_x, -_y}; }

Vector2 operator*(const float scalar, const Vector2& v) { return v * scalar; }
