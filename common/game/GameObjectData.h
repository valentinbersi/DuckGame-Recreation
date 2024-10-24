#pragma once

#include "Types.h"

enum class GameObjectID : u8 { OBJECT2D = 0 };

/**
 * Relevant data of an object in the game.
 */
class GameObjectData {
    GameObjectID _id;

protected:
    /**
     * Get the data of the object
     * @return The data of the object
     */
    virtual std::string _data();

public:
    GameObjectData() = delete;
    GameObjectData(const GameObjectData& other);
    GameObjectData& operator=(const GameObjectData& other);
    GameObjectData(GameObjectData&& other) noexcept;
    GameObjectData& operator=(GameObjectData&& other) noexcept;
    virtual ~GameObjectData();

    /**
     * Construct a GameObjectData with the given ObjectID
     * @param id The ID of the object
     */
    explicit GameObjectData(GameObjectID id);

    /**
     * Get the id of the object
     * @return The id of the object
     */
    [[nodiscard]] GameObjectID id() const;

    /**
     * Get the data of the object formatted to be sent to the client
     * @return The data of the object formatted to be sent to the client
     */
    [[nodiscard]] std::vector<char> data();
};
