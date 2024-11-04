#pragma once

#include <memory>

#include "Object2D.h"
#include "Shape2D.h"

/**
 * An Object that can collide with other collision objects
 */
class CollisionObject: public Object2D {
    u32 _collisionLayer;
    u32 _collisionMask;
    Shape2D* _shape;

protected:
    CollisionObject(const CollisionObject& other);
    CollisionObject& operator=(const CollisionObject& other);
    CollisionObject(CollisionObject&& other) noexcept;
    CollisionObject& operator=(CollisionObject&& other) noexcept;

    /**
     * Construct a CollisionObject2D with collision Layer and Mask = 0
     */
    CollisionObject(Object* parent, Vector2 position, float rotation, u32 collisionLayer,
                    u32 collisionMask, std::unique_ptr<Shape2D> shape);

    /**
     * Check if the CollisionObject collides with another CollisionObject
     * @param other the other CollisionObject to check collision with
     * @return true if the CollisionObject collides with the other CollisionObject, false otherwise
     */
    bool collidesWith(const CollisionObject& other) const;

public:
    CollisionObject() = delete;
    ~CollisionObject() override;

    /**
     * Update the shape's position
     * @param delta the time since the last update
     */
    void updateInternal(float delta) override;

    /**
     * Get the collision layers of the Object
     * @return the collision layers of the Object
     */
    u32 collisionLayer() const;

    /**
     * Get the collision mask of the Object
     * @return the collision mask of the Object
     */
    u32 collisionMask() const;

    /**
     * Activate collision for the given layer
     * @param layer the layer to activate collision for
     * @pre 0 <= layer <= 32
     */
    void activateCollisionLayer(u8 layer);

    /**
     * Deactivate collision for the given layer
     * @param layer the layer to deactivate collision for
     * @pre 0 <= layer <= 32
     */
    void deactivateCollisionLayer(u8 layer);

    /**
     * Activate the collision mask for the given layer
     * @param layer the layer to activate the collision mask for
     * @pre 0 <= layer <= 32
     */
    void activateCollisionMask(u8 layer);

    /**
     * Deactivate the collision mask for the given layer
     * @param layer the layer to deactivate the collision mask for
     * @pre 0 <= layer <= 32
     */
    void deactivateCollisionMask(u8 layer);

    /**
     * Check for collisions with other collision object and perform the collision
     * @param other the other object to check collision with
     */
    virtual void collideWith(const CollisionObject& other) = 0;
};
