#pragma once

#include "GameObjectData.h"
#include "Vector2.h"

/**
 * Relevant data for rendering a 2D object in the game
 */
class GameObject2DData: public GameObjectData {
    Vector2 _position;
    f32 _rotation;

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
    GameObject2DData(GameObjectID id, Vector2 position, f32 rotation);

    /**
     * Get the position of the 2D object
     * @return The position of the 2D object
     */
    [[nodiscard]] const Vector2& position() const;

    /**
     * Get the rotation of the 2D object
     * @return The rotation of the 2D object
     */
    [[nodiscard]] f32 rotation() const;

    /**
     * Get the data of the GameObject2DData
     * @return The data of the GameObject2DData
     */
    [[nodiscard]] std::string data() override;
};
