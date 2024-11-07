#pragma once

#include <forward_list>
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
    std::forward_list<std::weak_ptr<CollisionObject>> objectsToCollide;

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
     * Set the collision layer of the Object
     * @param collisionLayer the collision layer to set
     * @return this CollisionObject
     */
    CollisionObject& setCollisionLayer(u32 collisionLayer) noexcept;

    /**
     * Activate collision for the given layer
     * @param layer the layer to activate collision for
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, 31]
     * @pre 0 <= layer <= 31
     */
    CollisionObject& activateCollisionLayer(u8 layer);

    /**
     * Deactivate collision for the given layer
     * @param layer the layer to deactivate collision for
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, 31]
     * @pre 0 <= layer <= 31
     */
    CollisionObject& deactivateCollisionLayer(u8 layer);

    /**
     * Set the collision mask of the Object
     * @param collisionMask the collision mask to set
     * @return this CollisionObject
     */
    CollisionObject& setCollisionMask(u32 collisionMask) noexcept;

    /**
     * Activate the collision mask for the given layer
     * @param layer the layer to activate the collision mask for
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, 31]
     * @pre 0 <= layer <= 31
     */
    CollisionObject& activateCollisionMask(u8 layer);

    /**
     * Deactivate the collision mask for the given layer
     * @param layer the layer to deactivate the collision mask for
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, 31]
     * @pre 0 <= layer <= 31
     */
    CollisionObject& deactivateCollisionMask(u8 layer);

    /**
     * Register a collision to process, the collision will only be processed if this collision
     * object is scanning the given object layer
     * @param collisionObject the collision object to register
     */
    void registerCollision(std::weak_ptr<CollisionObject> collisionObject);

    /**
     * Reset the registered collisions
     */
    void resetRegisteredCollisions();

    /**
     * Check for collisions with other collision object and perform the collision
     */
    virtual void processCollisions() = 0;
};
