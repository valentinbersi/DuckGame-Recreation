#include "Level.h"

#include <algorithm>
#include <list>

#include "ItemSpawner.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

Level::Level(const LevelData& level, [[maybe_unused]] const HashMap<u16, Player*>& players) {
    for (u64 i = 0; i < level.terrainBlocks.size(); ++i) {
        auto block = new TerrainBlock(level.terrainBlocks[i]);
        terrainBlocks.push_back(block);
        addChild("TerrainBlock", block);
    }

    for (u64 i = 0; i < level.itemSpawnPoints.size(); ++i) {
        auto item = new ItemSpawner(level.itemSpawnPoints[i]);
        itemSpawners.push_back(item);
        addChild("ItemSpawner", item);
    }

    auto iterPlayers = players.begin();
    auto iterSpawnPoints = level.duckSpawnPoints.begin();
    while (iterPlayers != players.end() && iterSpawnPoints != level.duckSpawnPoints.end()) {
        iterPlayers->second->setPosition(*iterSpawnPoints);
        ++iterPlayers;
        ++iterSpawnPoints;
    }
}

std::list<SizedObjectData> Level::blockStatus() const {
    std::list<SizedObjectData> blockPositions;
    // for (const TerrainBlock* block: terrainBlocks) blockPositions.push_back(block->status());
    std::ranges::transform(terrainBlocks, std::back_inserter(blockPositions),
                           [](const TerrainBlock* block) { return block->status(); });
    return blockPositions;
}

std::list<SizedObjectData> Level::itemSpawnerStatus() const {
    std::list<SizedObjectData> itemPositions;
    // for (const ItemSpawner* itemSpawner: itemSpawners)
    //     itemPositions.push_back(itemSpawner->status());
    std::ranges::transform(itemSpawners, std::back_inserter(itemPositions),
                           [](const ItemSpawner* itemSpawner) { return itemSpawner->status(); });
    return itemPositions;
}
