#pragma once

#include <list>
#include <vector>

#include "Box.h"
#include "GameObject.h"
#include "ItemSpawner.h"
#include "LevelData.h"
#include "Player.h"
#include "SizedObjectData.h"
#include "TerrainBlock.h"


class Level final: public GameObject {
    std::vector<TerrainBlock*> terrainBlocks;
    std::vector<ItemSpawner*> itemSpawners;
    std::list<Box*> boxes;

    /**
     * Event manager for tree exited event
     * @param object The child that was removed
     */
    void onTreeExited(GameObject* object) override;

public:
    /**
     * Create a new Level object
     */
    explicit Level(const LevelData& level, const HashMap<u16, Player*>& players);

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

    /**
     * Get the position of all the boxes in the level
     * @return The positions of all the boxes in the level
     */
    std::list<SizedObjectData> boxStatus() const;

    /**
     * Destroy the Level object
     */
    ~Level() override;
};
