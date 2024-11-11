#pragma once

#include "GameObject.h"
#include "Vector2.h"

/**
 * 2D object with a position and rotation
 */
class GameObject2D: public GameObject {
    Vector2 _globalPosition;
    float _globalRotation;

    Vector2 _position;
    float _rotation;

protected:
    /**
     * Initialize an Object2D with a parent, a position a rotation and a scale
     * @param parent The parent of the object
     * @param position The position
     * @param rotation The rotation
     */
    GameObject2D(GameObject* parent, Vector2 position, float rotation);

public:
    GameObject2D() = delete;
    GameObject2D(const GameObject2D& other) = delete;
    GameObject2D& operator=(const GameObject2D& other) = delete;
    GameObject2D(GameObject2D&& other) noexcept = delete;
    GameObject2D& operator=(GameObject2D&& other) noexcept = delete;
    ~GameObject2D() override;

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
    GameObject2D& setGlobalPosition(Vector2 globalPosition) noexcept;

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
    GameObject2D& setGlobalRotation(float globalRotation) noexcept;

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
    GameObject2D& setPosition(Vector2 position) noexcept;

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
    GameObject2D& setRotation(float rotation) noexcept;

    /**
     * Get the local rotation of the object
     * @return The local rotation
     */
    [[nodiscard]] float rotation() const noexcept;
};
