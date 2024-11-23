#pragma once

#include "GameObject2DData.h"
#include "Rectangle.h"

struct SizedObjectData: GameObject2DData {
    Rectangle rectangle;

    SizedObjectData() = delete;
    SizedObjectData(const SizedObjectData& other);
    SizedObjectData& operator=(const SizedObjectData& other);
    SizedObjectData(SizedObjectData&& other) noexcept;
    SizedObjectData& operator=(SizedObjectData&& other) noexcept;
    ~SizedObjectData() override;

    /**
     * Construct a sized object data with the given position and rectangle
     * @param position the position
     * @param width the width
     * @param height the height
     */
    SizedObjectData(const Vector2& position, float width, float height);

    /**
     * Construct a sized object data with the given rectangle
     * @param rectangle the rectangle
     */
    explicit SizedObjectData(const Rectangle& rectangle);

    /**
     * Check if this sized object data is equal aproximatly to the other sized object data
     * @param other the other sized object data
     * @return true if the sized object data is equal aproximatly to the other sized object data
     */
    bool operator==(const SizedObjectData& other) const;
};
