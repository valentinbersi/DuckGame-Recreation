#pragma once

#include "Types.h"

enum class GameObjectID : u8 { Object2D = 0x0 };

/**
 * Relevant data of an object in the game.
 */
struct GameObjectData {
    GameObjectID objectID;

    GameObjectData() = delete;
    GameObjectData(const GameObjectData& other);
    GameObjectData& operator=(const GameObjectData& other);
    GameObjectData(GameObjectData&& other) noexcept;
    GameObjectData& operator=(GameObjectData&& other) noexcept;
    virtual ~GameObjectData();

    /**
     * Construct a GameObjectData with the given ObjectID
     * @param objectID The ID of the object
     */
    explicit GameObjectData(GameObjectID objectID);
};
