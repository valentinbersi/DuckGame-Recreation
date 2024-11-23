#pragma once

#include <list>
#include <vector>

#include "GameObject.h"
#include "LevelData.h"
#include "SizedObjectData.h"
#include "ItemSpawner.h"
#include "TerrainBlock.h"

class Level final: public GameObject {
    std::vector<TerrainBlock*> terrainBlocks;
    std::vector<ItemSpawner*> itemSpawner;

public:
    /**
     * Create a new Level object
     */
    explicit Level(const LevelData& level);

    /**
     * Get the position of all the blocks in the level
     * @return The positions of all the blocks in the level
     */
    std::list<SizedObjectData> blockStatus() const;

    /**
     * Get the position of all the item spawner in the level
     * @return The positions of all the item spawner in the level
     */
    std::list<SizedObjectData> itemSpawnerStatus() const;
};
