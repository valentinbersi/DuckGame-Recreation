#include "Level.h"

#include <list>

#include "ItemSpawner.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

Level::Level(const LevelData& level) {
    for (u64 i = 0; i < level.terrainBlocks.size(); ++i) {
        auto block = new TerrainBlock(level.terrainBlocks[i]);
        terrainBlocks.push_back(block);
        addChild("TerrainBlock", block);
    }

    for (u64 i = 0; i < level.itemSpawnPoints.size(); ++i) {
        auto item = new ItemSpawner(level.itemSpawnPoints[i]);
        itemSpawner.push_back(item);
        addChild("ItemSpawner", item);
    }

    for (u64 i = 0; i < level.duckSpawnPoints.size(); ++i)
        addChild("SpawnPoint", new SpawnPoint(level.duckSpawnPoints[i]));
}

std::list<SizedObjectData> Level::blockStatus() const {
    std::list<SizedObjectData> blockPositions;
    for (const auto& block: terrainBlocks) blockPositions.push_back(block->status());
    return blockPositions;
}

std::list<SizedObjectData> Level::itemSpawnerStatus() const {
    std::list<SizedObjectData> itemPositions;
    for (const auto& item: itemSpawner) itemPositions.push_back(item->status());
    return itemPositions;
}
