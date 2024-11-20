#pragma once

#include "Vector2.h"

/**
 * Relevant data for rendering a 2D object in the game
 */
struct GameObject2DData {
    Vector2 position;

    GameObject2DData() = delete;
    GameObject2DData(const GameObject2DData& other);
    GameObject2DData& operator=(const GameObject2DData& other);
    GameObject2DData(GameObject2DData&& other) noexcept;
    GameObject2DData& operator=(GameObject2DData&& other) noexcept;
    virtual ~GameObject2DData();

    /**
     * Construct a GameObject2DData with the given position
     * @param position The position of the GameObject2D
     */
    explicit GameObject2DData(Vector2 position);
};
