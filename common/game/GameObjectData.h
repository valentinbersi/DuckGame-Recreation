#pragma once

#include "Types.h"

enum class GameObjectID : u8 { PLAYER = 0, ENEMY = 1, BULLET = 2, BLOCK = 3 };

/**
 * Relevant data of an object in the game.
 */
class GameObjectData {
    GameObjectID _id;

public:
    GameObjectData() = delete;
    GameObjectData(const GameObjectData& other);
    GameObjectData& operator=(const GameObjectData& other);
    GameObjectData(GameObjectData&& other) noexcept;
    GameObjectData& operator=(GameObjectData&& other) noexcept;
    virtual ~GameObjectData();

    explicit GameObjectData(GameObjectID id);

    [[nodiscard]] GameObjectID id() const;
};
