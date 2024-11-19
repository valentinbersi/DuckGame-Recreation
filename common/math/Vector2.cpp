#include "Vector2.h"

#include <cmath>
#include <stdexcept>

#include "Math.h"

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::UP(0, -1);
const Vector2 Vector2::DOWN(0, 1);
const Vector2 Vector2::LEFT(-1, 0);
const Vector2 Vector2::RIGHT(1, 0);
const Vector2 Vector2::NANV(NAN, NAN);
const Vector2 Vector2::ONE(1, 1);

#define DEFAULT_VALUE 0

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

float Vector2::x() const { return _x; }

float Vector2::y() const { return _y; }

Vector2 Vector2::x(float value) const { return {value, _y}; }

Vector2 Vector2::y(float value) const { return {_x, value}; }

void Vector2::setX(const float x) { _x = x; }

void Vector2::setY(const float y) { _y = y; }

#define ANGLE "Vector2::angle()"
#define UNDEFINED_FOR_ZERO " is undefined for (0, 0) vector"

float Vector2::angle() const {
    if (isZero())
        throw std::logic_error(ANGLE UNDEFINED_FOR_ZERO);

    return std::atan2(_y, _x);
}

#define ANGLE_RESPECT_TO "Vector2::angle(const Vector2&)"
#define UNDEFINED_FOR_ZERO_V " is undefined for (0, 0) v argument"

float Vector2::angle(const Vector2& v) const {
    if (isZero())
        throw std::logic_error(ANGLE_RESPECT_TO UNDEFINED_FOR_ZERO);

    if (v.isZero())
        throw std::invalid_argument(ANGLE_RESPECT_TO UNDEFINED_FOR_ZERO_V);

    return std::acos(cross(v) / dot(v));
}

#define BOUNCE "Vector2::bounce(const Vector2&)"

Vector2 Vector2::bounce(const Vector2& normal) const {
    try {
        return -reflect(normal);
    } catch ([[maybe_unused]] const std::logic_error& e) {
        throw std::logic_error(BOUNCE UNDEFINED_FOR_ZERO);
    }
}

float Vector2::cross(const Vector2& v) const noexcept { return _x * v._y - _y * v._x; }

#define DIRECTION_TO "Vector2::directionTo(const Vector2&)"

Vector2 Vector2::directionTo(const Vector2& v) const {
    const Vector2 result = v - *this;

    try {
        return result.normalized();
    } catch ([[maybe_unused]] const std::logic_error& e) {
        throw std::logic_error(DIRECTION_TO UNDEFINED_FOR_ZERO);
    }
}

float Vector2::distance(const Vector2& v) const { return (*this - v).length(); }

float Vector2::distanceSquared(const Vector2& v) const { return (*this - v).lengthSquared(); }

float Vector2::dot(const Vector2& v) const noexcept { return _x * v._x + _y * v._y; }

bool Vector2::operator==(const Vector2& v) const noexcept {
    return Math::isEqualAprox(_x, v._x) && Math::isEqualAprox(_y, v._y);
}

bool Vector2::operator!=(const Vector2& v) const noexcept { return !(*this == v); }

bool Vector2::isNormalized() const noexcept { return Math::isEqualAprox(lengthSquared(), 1); }

bool Vector2::isZero() const noexcept { return _x == 0 and _y == 0; }

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

#define NORMALIZED "Vector2::normalized()"

Vector2 Vector2::normalized() const {
    if (isZero())
        throw std::logic_error(NORMALIZED UNDEFINED_FOR_ZERO);

    return *this / length();
}

Vector2 Vector2::orthogonal() const { return {_y, -_x}; }

#define PROJECT "Vector2::normalized()"

Vector2 Vector2::project(const Vector2& v) const {
    if (v.isZero())
        throw std::logic_error(PROJECT UNDEFINED_FOR_ZERO_V);

    if (isZero())
        return ZERO;

    return (dot(v) / v.lengthSquared()) * v;
}

#define REFLECT "Vector2::reflect(const Vector2&)"
#define UNDEFINED_FOR_ZERO_NORMAL " is undefined for (0, 0) normal argument"

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

void Vector2::swap() { std::swap(_x, _y); }

void Vector2::swapX(Vector2& other) { std::swap(_x, other._x); }

void Vector2::swapY(Vector2& other) { std::swap(_y, other._y); }

Vector2 Vector2::operator*(const float scalar) const { return {scalar * _x, scalar * _y}; }

Vector2& Vector2::operator*=(const float scalar) { return *this = *this * scalar; }

Vector2 Vector2::operator+(const Vector2& v) const { return {v._x + _x, v._y + _y}; }

Vector2& Vector2::operator+=(const Vector2& v) {
    _x += v._x;
    _y += v._y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const { return {_x - v._x, _y - v._y}; }

Vector2& Vector2::operator-=(const Vector2& v) { return *this = *this - v; }

#define DIVISION_BY_ZERO "Vector2::operator/(real) is undefined for 0 scalar"

Vector2 Vector2::operator/(const float scalar) const {
    if (Math::isZeroAprox(scalar))
        throw std::logic_error(DIVISION_BY_ZERO);

    return {_x / scalar, _y / scalar};
}

Vector2& Vector2::operator/=(const float scalar) { return *this = *this / scalar; }

Vector2 Vector2::operator/(const Vector2& other) const { return {_x / other._x, _y / other._y}; }

Vector2& Vector2::operator/=(const Vector2& other) {
    _x /= other._x;
    _y /= other._y;
    return *this;
}

Vector2 Vector2::operator*(const Vector2& other) const { return {_x * other._x, _y * other._y}; }

Vector2& Vector2::operator*=(const Vector2& other) {
    _x *= other._x;
    _y *= other._y;
    return *this;
}

const Vector2& Vector2::operator+() const { return *this; }

Vector2 Vector2::operator-() const { return {-_x, -_y}; }

Vector2::Orientation Vector2::orientation(const Vector2& p, const Vector2& q, const Vector2& r) {
    const float val = (q - p).cross(r - q);
    if (val == 0)
        return Orientation::Collinear;
    return val > 0 ? Orientation::CounterClockwise : Orientation::Clockwise;
}

Vector2 operator*(const float scalar, const Vector2& v) { return v * scalar; }
