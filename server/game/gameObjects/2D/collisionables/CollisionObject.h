#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "GameObject2D.h"
#include "Rectangle.h"

/**
 * An Object that can collide with other collision objects
 */
class CollisionObject: public GameObject2D {
public:
    constexpr static u8 LayersCount = 32;

private:
    std::bitset<LayersCount> _layers;
    std::bitset<LayersCount> _scannedLayers;

protected:
    Rectangle shape;
    std::vector<std::weak_ptr<CollisionObject>> objectsToCollide;

    /**
     * Construct a CollisionObject with the given parent, position, rotation, layers, scanned
     * layers, and a rectangle shape
     * @param parent the parent Object
     * @param position the position of the CollisionObject
     * @param layers the layers that the object is in
     * @param scannedLayers the layers the object scans in search for other collisionObjects
     * @param width the width of the CollisionObject
     * @param height the height of the CollisionObject
     */
    CollisionObject(GameObject* parent, const Vector2& position, std::bitset<LayersCount> layers,
                    std::bitset<LayersCount> scannedLayers, float width, float height);


    /**
     * Check if the CollisionObject collides with another CollisionObject.\n
     * This method only checks the shape, layers are checked when registering collisions
     * @param other the other CollisionObject to check collision with
     * @return true if the CollisionObject collides with the other CollisionObject, false otherwise
     */
    bool collidesWith(const CollisionObject& other) const;

    /**
     * Move the CollisionObject and check for collisions with another CollisionObject
     * @param other the other CollisionObject to check collision with
     * @param displacement the displacement to move the CollisionObject
     */
    std::optional<IntersectionInfo> moveAndCollide(const CollisionObject& other,
                                                   const Vector2& displacement, float delta) const;

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
     * Set the position of the object
     * @param position the new position
     * @return this CollisionObject
     */
    GameObject2D& setPosition(Vector2 position) noexcept final;

    /**
     * Get the collision layers of the Object
     * @return the collision layers of the Object
     */
    std::bitset<LayersCount> layers() const;

    /**
     * Get the layers that this object scans
     * @return the layers that this object scans
     */
    std::bitset<LayersCount> scannedLayers() const;

    /**
     * Set the layers of the Object
     * @param layers the collision layers to set
     * @return this CollisionObject
     */
    CollisionObject& setLayers(std::bitset<LayersCount> layers) noexcept;

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
    CollisionObject& setScannedLayers(std::bitset<LayersCount> scannedLayers) noexcept;

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
    virtual void registerCollision(std::weak_ptr<CollisionObject> collisionObject);

    /**
     * Reset the registered collisions
     */
    void resetRegisteredCollisions();

    /**
     * Check for collisions with other collision object and perform the collision
     * @param delta the time since the last update
     */
    virtual void processCollisions(float delta) = 0;
};
