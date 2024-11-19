#pragma once

#include "GameObject.h"
#include "Vector2.h"

/**
 * 2D object with a position
 */
class GameObject2D: public GameObject {
    Vector2 _globalPosition;
    Vector2 _position;

protected:
    /**
     * Initialize an Object2D with a parent, a position a rotation and a scale
     * @param parent The parent of the object
     * @param position The position
     */
    GameObject2D(GameObject* parent, Vector2 position);

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
     * Set the local position of the object
     * @param position The new local position
     * @return A reference to this object, to allow builder pattern.
     */
    virtual GameObject2D& setPosition(Vector2 position) noexcept;

    /**
     * Get the local position of the object
     * @return The local position
     */
    [[nodiscard]] const Vector2& position() const noexcept;
};
