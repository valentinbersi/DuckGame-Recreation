#pragma once

#include "Types.h"

/**
 * Relevant data of an object in the game.
 */
class ObjectData {
    u32 _id;

public:
    ObjectData() = delete;
    ObjectData(const ObjectData& other);
    ObjectData& operator=(const ObjectData& other);
    ObjectData(ObjectData&& other) noexcept;
    ObjectData& operator=(ObjectData&& other) noexcept;
    virtual ~ObjectData();

    explicit ObjectData(u32 id);

    [[nodiscard]] u32 id() const;
};
