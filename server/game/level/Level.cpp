#include "Level.h"

#include <list>

#include "ItemSpawner.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

Level::Level(const LevelData& level): GameObject(nullptr) {
    for (u64 i = 0; i < level.terrainBlocks.size(); ++i) {
        auto block = new TerrainBlock(level.terrainBlocks[i]);
        terrainBlocks.push_back(block);
        addChild("TerrainBlock" + std::to_string(i), block);
    }

    for (u64 i = 0; i < level.itemSpawnPoints.size(); ++i) {
        auto item = new ItemSpawner(level.itemSpawnPoints[i]);
        itemSpawner.push_back(item);
        addChild("ItemSpawner" + std::to_string(i), item);
    }

    for (u64 i = 0; i < level.duckSpawnPoints.size(); ++i)
        addChild("SpawnPoint" + std::to_string(i), new SpawnPoint(level.duckSpawnPoints[i]));
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
