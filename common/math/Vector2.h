#pragma once

/**
 * A mathematical vector for two dimensions. All operations are done in x = (1, 0) and y = (0, 1)
 * reference system.
 */
class Vector2 {
    float _x, _y;

public:
    /**
     * A vector will all its coordinates set to 0
     */
    static const Vector2 ZERO;
    /**
     * A vector pointing UP (0, -1)
     */
    static const Vector2 UP;
    /**
     * A vector pointing DOWN (0, 1)
     */
    static const Vector2 DOWN;
    /**
     * A vector pointing LEFT (-1, 0)
     */
    static const Vector2 LEFT;
    /**
     * A vector pointing RIGHT (1, 0)
     */
    static const Vector2 RIGHT;

    /**
     * Construct a default initialized Vector2 with all coordinates set to 0
     */
    Vector2() noexcept;
    Vector2(const Vector2& other) noexcept;
    Vector2& operator=(const Vector2& other) noexcept;
    Vector2(Vector2&& other) noexcept;
    Vector2& operator=(Vector2&& other) noexcept;
    ~Vector2() noexcept;

    /**
     * Contruct a Vector2 with the given x and y
     * @param x The x coordinate
     * @param y The y coordinate
     */
    Vector2(float x, float y) noexcept;

    /**
     * Construct a unit vector rotated to the given angle in radians.
     * @param angle The angle in radians
     */
    explicit Vector2(float angle) noexcept;

    /**
     * Get the x coordinate of the vector
     * @return The x coordinate
     */
    [[nodiscard]] float x() const;

    /**
     * Get the y coordinate of the vector
     * @return The y coordinate
     */
    [[nodiscard]] float y() const;

    /**
     * Set the x coordinate of the vector
     * @param x The new x coordinate
     */
    void x(float x);

    /**
     * Set the y coordinate of the vector
     * @param y The new y coordinate
     */
    void y(float y);

    /**
     * Get this vector's angle with respect to the positive X axis, or RIGHT (1, 0)
     * vector, in radians
     * @return The angle in radians
     */
    [[nodiscard]] float angle() const;

    /**
     * Get the angle to the given vector, in radians
     * @param v The other vector
     * @return The angle in radians
     */
    [[nodiscard]] float angle(const Vector2& v) const;

    /**
     * Get the vector "bounced off" from a line defined by the given normal perpendicular to the
     * line
     * @param normal The normal vector
     * @return The bounced vector
     */
    [[nodiscard]] Vector2 bounce(const Vector2& normal) const;

    /**
     * Embed the vectors on the XY plane of a 3D space and get the vector's cross-product's z
     * component.\n
     * Same as calculating the signed area of the parallelogram formed by the vectors.\n
     * If the vectors are parallel, returns 0.
     * @param v The other vector
     * @return The size of the resulting vector
     */
    [[nodiscard]] float cross(const Vector2& v) const noexcept;

    /**
     * Get a normalized vector pointing to v
     * @param v The other vector
     * @return A normalized vector pointing to v
     */
    [[nodiscard]] Vector2 directionTo(const Vector2& v) const;

    /**
     * Get the distance between this vector and v
     * @param v The other vector
     * @return The distance between this vector and v
     */
    [[nodiscard]] float distance(const Vector2& v) const;

    /**
     * Get the dot product of this vector and v
     * @param v The other vector
     * @return The dot product of this vector and v
     */
    [[nodiscard]] float dot(const Vector2& v) const noexcept;

    /**
     * Check if the vector is approximately equal to the given vector.
     * @return True if the vectors are approximately equal
     */
    [[nodiscard]] bool operator==(const Vector2& v) const noexcept;

    /**
     * Check if the vector is not approximately equal to the given vector.
     * @return True if the vectors are not approximately equal
     */
    [[nodiscard]] bool operator!=(const Vector2& v) const noexcept;

    /**
     * Check if the vector is normalized
     * @return True if the vector is normalized
     */
    [[nodiscard]] bool isNormalized() const noexcept;

    /**
     * Check if the vector is approximately equal to the zero vector. Faster than comparing to the
     * ZERO vector
     * @return True if the vector is approximately equal to the zero vector
     */
    [[nodiscard]] bool isZero() const noexcept;

    /**
     * Get the length of the vector
     * @return The length of the vector
     */
    [[nodiscard]] float length() const noexcept;

    /**
     * Get the squared length of the vector. Faster than length() for comparisons.
     * @return The squared length of the vector
     */
    [[nodiscard]] float lengthSquared() const noexcept;

    /**
     * Get the result of scaling the vector to one unit length.
     * @return The normalized vector
     */
    [[nodiscard]] Vector2 normalized() const;

    /**
     * Get a perpendicular vector rotated 90 degrees counter-clockwise compared to the original,
     * with the same lenght.
     */
    [[nodiscard]] Vector2 orthogonal() const;

    /**
     * Get the vector projected onto the given vector
     * @param v The vector to project onto
     * @return The projected vector
     */
    [[nodiscard]] Vector2 project(const Vector2& v) const;

    /**
     * Get the vector reflected from a line defined by the given normal perpendicular to the
     * line
     * @param normal The normal vector
     * @return The reflected vector
     */
    [[nodiscard]] Vector2 reflect(const Vector2& normal) const;

    /**
     * Get the vector rotated by the given angle in radians
     * @param angle The angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vector2 rotated(float angle) const;

    /**
     * Get the result of scaling the vector by the given scalar
     * @param scalar The scalar to multiply the vector by
     * @return The scaled vector
     */
    [[nodiscard]] Vector2 operator*(float scalar) const;

    /**
     * Get the result of scaling the vector by the given scalar and store it in this vector
     * @param scalar The scalar to multiply the vector by
     * @return A reference to this vector
     */
    Vector2& operator*=(float scalar);

    /**
     * Get the result of adding the given vector to this vector
     * @param v The vector to add
     * @return The sum of the vectors
     */
    [[nodiscard]] Vector2 operator+(const Vector2& v) const;

    /**
     * Get the result of adding the given vector to this vector and store it in this vector
     * @param v The vector to add
     * @return A reference to this vector
     */
    Vector2& operator+=(const Vector2& v);

    /**
     * Get the result of subtracting the given vector to this vector
     * @param v The vector to subtract
     * @return The difference of the vectors
     */
    [[nodiscard]] Vector2 operator-(const Vector2& v) const;

    /**
     * Get the result of subtracting the given vector to this vector and store it in this vector
     * @param v The vector to subtract
     * @return A reference to this vector
     */
    Vector2& operator-=(const Vector2& v);

    /**
     * Get the result of dividing the vector by the given scalar
     * @param scalar The scalar to divide the vector by
     * @return The divided vector
     */
    [[nodiscard]] Vector2 operator/(float scalar) const;

    /**
     * Get the result of dividing the vector by the given scalar and store it in this vector
     * @param scalar The scalar to divide the vector by
     * @return A reference to this vector
     */
    Vector2& operator/=(float scalar);

    /**
     * Get the same vector. May be useful for improving code readability.
     * @return The same vector
     */
    const Vector2& operator+() const;

    /**
     * Get the vector with the opposite direction
     * @return The opposite vector
     */
    [[nodiscard]] Vector2 operator-() const;

    /**
     * Get the result of scaling the vector by the given scalar
     * @param scalar The scalar to multiply the vector by
     * @param v The vector to scale
     * @result The scaled vector
     */
    friend Vector2 operator*(float scalar, const Vector2& v);
};
