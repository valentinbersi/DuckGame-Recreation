#include "Level.h"

#include <algorithm>
#include <list>

#include "ItemSpawner.h"
#include "Layer.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

Level::Level(const LevelData& level, const HashMap<u16, Player*>& players) {
    addChild("Death zone", new StaticObject({static_cast<float>(level.width) / 2, -20}, Layer::Wall,
                                            Layer::None, static_cast<float>(level.width), 40));

    addChild("Death zone",
             new StaticObject(
                     {static_cast<float>(level.width) / 2, static_cast<float>(level.height) + 20},
                     Layer::DeathZone, Layer::None, static_cast<float>(level.width), 40));

    addChild("Death zone",
             new StaticObject({-20, static_cast<float>(level.height) / 2}, Layer::Wall, Layer::None,
                              40, static_cast<float>(level.height)));

    addChild("Death zone",
             new StaticObject(
                     {static_cast<float>(level.width) + 20, static_cast<float>(level.height) / 2},
                     Layer::Wall, Layer::None, 40, static_cast<float>(level.height)));

    for (const auto& terrainBlock: level.terrainBlocks) {
        auto block = new TerrainBlock(terrainBlock);
        terrainBlocks.push_back(block);
        addChild("TerrainBlock", block);
    }

    for (const auto& itemSpawnPoint: level.itemSpawnPoints) {
        auto item = new ItemSpawner(itemSpawnPoint);
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
    // for (const TerrainBlock* block: terrainBlocks)
    // blockPositions.push_back(block->status());
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
