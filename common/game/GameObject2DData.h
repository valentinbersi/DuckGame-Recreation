#pragma once

#include "GameObjectData.h"
#include "../math/Vector2.h"
#include <cstdint>
#include <memory>

using u8 = std::uint8_t;

enum class GameObject2DID : u8 { Duck = 0x0 };

/**
 * Relevant data for rendering a 2D object in the game
 */
struct GameObject2DData: GameObjectData {
    GameObject2DID object2DID;
    Vector2 position;
    float rotation;

    GameObject2DData() = delete;
    GameObject2DData(const GameObject2DData& other);
    GameObject2DData& operator=(const GameObject2DData& other);
    GameObject2DData(GameObject2DData&& other) noexcept;
    GameObject2DData& operator=(GameObject2DData&& other) noexcept;
    ~GameObject2DData() override;

    /**
     * Construct a GameObject2DData with the given id, position and rotation
     * @param object2DID The id of the GameObject2D
     * @param position The position of the GameObject2D
     * @param rotation The rotation of the GameObject2D
     */
    GameObject2DData(GameObject2DID object2DID, Vector2 position, float rotation);
};
