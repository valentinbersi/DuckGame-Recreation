#pragma once

#include <forward_list>
#include <memory>

#include "Object2D.h"
#include "Shape2D.h"

/**
 * An Object that can collide with other collision objects
 */
class CollisionObject: public Object2D {
public:
    constexpr static u8 LAYERS_COUNT = 32;

private:
    std::bitset<LAYERS_COUNT> _layers;
    std::bitset<LAYERS_COUNT> _scannedLayers;
    Shape2D* shape;

protected:
    std::forward_list<std::weak_ptr<CollisionObject>> objectsToCollide;

    /**
     * Construct a CollisionObject with the given parent, position, rotation, layers, scanned
     * layers, and shape
     * @param parent the parent Object
     * @param position the position of the CollisionObject
     * @param rotation the rotation of the CollisionObject
     * @param layers the layers that the object is in
     * @param scanning the layers the object scans in search for other collisionObjects
     * @param shape the shape of the CollisionObject
     */
    CollisionObject(Object* parent, Vector2 position, float rotation,
                    std::bitset<LAYERS_COUNT> layers, std::bitset<LAYERS_COUNT> scanning,
                    std::unique_ptr<Shape2D> shape);

    /**
     * Check if the CollisionObject collides with another CollisionObject.\n
     * This method only checks the shape, layers are checked when registering collisions
     * @param other the other CollisionObject to check collision with
     * @return true if the CollisionObject collides with the other CollisionObject, false otherwise
     */
    bool collidesWith(const CollisionObject& other) const;

public:
    CollisionObject() = delete;
    CollisionObject(const CollisionObject& other) = delete;
    CollisionObject& operator=(const CollisionObject& other) = delete;
    CollisionObject(CollisionObject&& other) noexcept = delete;
    CollisionObject& operator=(CollisionObject&& other) noexcept = delete;
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
    std::bitset<LAYERS_COUNT> layers() const;

    /**
     * Get the layers that this object scans
     * @return the layers that this object scans
     */
    std::bitset<LAYERS_COUNT> scannedLayers() const;

    /**
     * Set the layers of the Object
     * @param layers the collision layers to set
     * @return this CollisionObject
     */
    CollisionObject& setLayers(std::bitset<LAYERS_COUNT> layers) noexcept;

    /**
     * Adds the object to the given layer
     * @param layer the layer in which the object is going to be added
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, @code LAYER_COUNT@endcode)
     * @pre 0 <= layer < @code LAYER_COUNT@endcode
     */
    CollisionObject& addToLayer(u8 layer);

    /**
     * Remove the object from the given layer
     * @param layer the layer from which the object is going to be removed
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, @code LAYER_COUNT@endcode)
     * @pre 0 <= layer < @code LAYER_COUNT@endcode
     */
    CollisionObject& removeFromLayer(u8 layer);

    /**
     * Set the scanned layers of the Object
     * @param scannedLayers the scanned layers to set
     * @return this CollisionObject
     */
    CollisionObject& setScannedLayers(std::bitset<LAYERS_COUNT> scannedLayers) noexcept;

    /**
     * Add a layer to the scanned layers
     * @param layer the layer to be scanned by this object
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, @code LAYER_COUNT@endcode)
     * @pre 0 <= layer < @code LAYER_COUNT@endcode
     */
    CollisionObject& addLayerToScan(u8 layer);

    /**
     * Remove a layer from the scanned layers
     * @param layer the layer to stop being scanned by this object
     * @return this CollisionObject
     * @exception std::out_of_range if layer is not in the range [0, @code LAYER_COUNT@endcode)
     * @pre 0 <= layer < @code LAYER_COUNT@endcode
     */
    CollisionObject& removeLayerToScan(u8 layer);

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
