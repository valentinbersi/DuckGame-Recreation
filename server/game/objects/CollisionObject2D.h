#pragma once

#include "Object2D.h"

class CollisionObject2D: public Object2D {
    u32 _collisionLayer;
    u32 _collisionMask;
    // Shape2D _shape;

protected:
    /**
     * Construct a CollisionObject2D with the given parent, position = (0, 0), rotation = 0, scale =
     * (1, 1), collision Layer and Mask = 0
     */
    explicit CollisionObject2D(Object* parent);

    /**
     * Construct a CollisionObject2D with collision Layer and Mask = 0
     */
    CollisionObject2D(Object* parent, Vector2 position, f32 rotation, u32 collisionLayer,
                      u32 collisionMask /*, Shape2D shape*/);

public:


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
     * Check if this object collides with the other object. If it does, emit the "bodyEntered" event
     * with the given CollisionObject as argument
     * @param other the other object to check collision with
     */
    void collideWith(CollisionObject2D& other);
};
