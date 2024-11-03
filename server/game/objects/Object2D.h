#pragma once

#include "Object.h"
#include "Vector2.h"

/**
 * 2D object with a position, rotation and scale
 */
class Object2D: public Object {
    Vector2 _globalPosition;
    float _globalRotation;

    Vector2 _position;
    float _rotation;

protected:
    Object2D(const Object2D& other);
    Object2D& operator=(const Object2D& other);
    Object2D(Object2D&& other) noexcept;
    Object2D& operator=(Object2D&& other) noexcept;

    /**
     * Initialize an Object2D with a parent, a position a rotation and a scale
     * @param parent The parent of the object
     * @param position The position
     * @param rotation The rotation
     */
    Object2D(Object* parent, Vector2 position, float rotation);

public:
    /**
     * Initialize an Object2D with position (0, 0), rotation 0 and scale (1, 1)
     */
    Object2D() = delete;
    ~Object2D() override;

    /**
     * Update the object global position and rotation based on the parent
     * @param delta The time since the last update
     */
    void updateInternal(float delta) override;

    /**
     * Set the global position of the object
     * @param globalPosition The new global position
     * @return A reference to this object, to allow builder pattern.
     */
    Object2D& setGlobalPosition(Vector2 globalPosition) noexcept;

    /**
     * Get the global position of the object
     * @return The global position
     */
    [[nodiscard]] const Vector2& globalPosition() const noexcept;

    /**
     * Set the global rotation of the object
     * @param globalRotation The new global rotation
     * @return A reference to this object, to allow builder pattern.
     */
    Object2D& setGlobalRotation(float globalRotation) noexcept;

    /**
     * Get the global rotation of the object
     * @return The global rotation
     */
    [[nodiscard]] float globalRotation() const noexcept;

    /**
     * Set the local position of the object
     * @param position The new local position
     * @return A reference to this object, to allow builder pattern.
     */
    Object2D& setPosition(Vector2 position) noexcept;

    /**
     * Get the local position of the object
     * @return The local position
     */
    [[nodiscard]] const Vector2& position() const noexcept;

    /**
     * Set the local rotation of the object
     * @param rotation The new local rotation
     * @return A reference to this object, to allow builder pattern.
     */
    Object2D& setRotation(float rotation) noexcept;

    /**
     * Get the local rotation of the object
     * @return The local rotation
     */
    [[nodiscard]] float rotation() const noexcept;
};
