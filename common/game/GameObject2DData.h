#pragma once

#include "GameObjectData.h"
#include "Vector2.h"

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

    GameObject2DData(GameObjectID id, Vector2 position, f32 rotation);

    [[nodiscard]] const Vector2& position() const;

    [[nodiscard]] f32 rotation() const;
};
