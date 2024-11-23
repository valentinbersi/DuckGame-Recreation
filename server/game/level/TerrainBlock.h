#pragma once

#include "SizedObjectData.h"
#include "StaticObject.h"

/**
 * A platform in the game
 */
class TerrainBlock final: public StaticObject {
public:
    /**
     * Creates a new TerrainBlock
     * @param position the position of the TerrainBlock
     */
    explicit TerrainBlock(Vector2 position);

    SizedObjectData status();
};
