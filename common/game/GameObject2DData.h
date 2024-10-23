#pragma once

#include "GameObjectData.h"
#include "Vector2.h"

enum class GameObject2DID : u8 { DUCK = 0, GUN = 1, BULLET = 2, WALL = 3 };

/**
 * Relevant data for rendering a 2D object in the game
 */
class GameObject2DData: public GameObjectData {
    GameObject2DID _id;
    Vector2 _position;
    f32 _rotation;

protected:
    std::string _data() override;

public:
    GameObject2DData() = delete;
    GameObject2DData(const GameObject2DData& other);
    GameObject2DData& operator=(const GameObject2DData& other);
    GameObject2DData(GameObject2DData&& other) noexcept;
    GameObject2DData& operator=(GameObject2DData&& other) noexcept;
    ~GameObject2DData() override;

    /**
     * Construct a GameObject2DData with the given id, position and rotation
     * @param id The id of the GameObject2D
     * @param position The position of the GameObject2D
     * @param rotation The rotation of the GameObject2D
     */
    GameObject2DData(GameObject2DID id, Vector2 position, f32 rotation);

    /**
     * Get the position of the 2D object
     * @return The position of the 2D object
     */
    [[nodiscard]] const Vector2& position() const;

    /**
     * Get the id of the 2D object
     * @return The id of the 2D object
     */
    [[nodiscard]] GameObject2DID id2D() const;

    /**
     * Get the rotation of the 2D object
     * @return The rotation of the 2D object
     */
    [[nodiscard]] f32 rotation() const;
};
