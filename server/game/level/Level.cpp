#include "Level.h"

#include <list>

#include "SpawnPoint.h"
#include "TerrainBlock.h"

Level::Level(const LevelData& level): GameObject(nullptr) {
    for (u64 i = 0; i < level.terrainBlocks.size(); ++i) {
        auto block = new TerrainBlock(level.terrainBlocks[i]);
        terrainBlocks.push_back(block);
        addChild("TerrainBlock" + std::to_string(i), block);
    }

    for (u64 i = 0; i < level.duckSpawnPoints.size(); ++i)
        addChild("SpawnPoint" + std::to_string(i), new SpawnPoint(level.duckSpawnPoints[i]));
}

std::list<Vector2> Level::status() const {
    std::list<Vector2> blockPositions;
    for (const auto& block: terrainBlocks) blockPositions.push_back(block->position());
    return blockPositions;
}
