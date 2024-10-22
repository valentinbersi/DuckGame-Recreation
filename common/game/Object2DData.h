#pragma once

#include "ObjectData.h"
#include "Vector2.h"

class Object2DData: public ObjectData {
    Vector2 _position;
    f32 _rotation;

public:
    Object2DData() = delete;
    Object2DData(const Object2DData& other);
    Object2DData& operator=(const Object2DData& other);
    Object2DData(Object2DData&& other) noexcept;
    Object2DData& operator=(Object2DData&& other) noexcept;
    ~Object2DData() override;

    Object2DData(u32 id, Vector2 position, f32 rotation);

    [[nodiscard]] const Vector2& position() const;

    [[nodiscard]] f32 rotation() const;
};
