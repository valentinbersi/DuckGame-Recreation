#pragma once

#include <list>
#include <vector>

#include "GameObject.h"
#include "LevelData.h"
#include "TerrainBlock.h"

class Level final: public GameObject {
    std::vector<TerrainBlock*> terrainBlocks;

public:
    /**
     * Create a new Level object
     */
    explicit Level(const LevelData& level);

    /**
     * Get the position of all the blocks in the level
     * @return The positions of all the blocks in the level
     */
    std::list<Vector2> status() const;
};
