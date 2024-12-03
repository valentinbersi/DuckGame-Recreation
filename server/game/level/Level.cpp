#include "Level.h"

#include <algorithm>
#include <list>

#include "Explosion.h"
#include "ItemSpawner.h"
#include "Layer.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

#define eventHandler(Function, ...) \
    gameObject::EventHandler<Level, __VA_ARGS__>::create(getReference<Level>(), Function)

void Level::onTreeEntered(GameObject* object) {
    if (const auto explosion = dynamic_cast<Explosion*>(object); explosion != nullptr) {
        explosions.push_back(explosion);
    }
}

void Level::onTreeExited(GameObject* object) {
    if (const auto box = dynamic_cast<Box*>(object); box != nullptr) {
        boxes.remove(box);
    }
    if (const auto explosion = dynamic_cast<Explosion*>(object); explosion != nullptr) {
        explosions.remove(explosion);
    }
}

Level::Level(const LevelData& level, const HashMap<u16, Player*>& players):
        background(level.background) {
    connect(Events::TreeEntered, eventHandler(&Level::onTreeEntered, GameObject*));
    connect(Events::TreeExited, eventHandler(&Level::onTreeExited, GameObject*));

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

    for (const auto& boxPosition: level.boxes) {
        auto box = new Box(boxPosition);
        boxes.push_back(box);
        addChild("Box", box);
    }

    auto iterPlayers = players.begin();
    auto iterSpawnPoints = level.duckSpawnPoints.begin();
    while (iterPlayers != players.end() && iterSpawnPoints != level.duckSpawnPoints.end()) {
        iterPlayers->second->setPosition(*iterSpawnPoints);
        ++iterPlayers;
        ++iterSpawnPoints;
    }
}

BackgroundID Level::getBackground() const { return background; }

std::list<SizedObjectData> Level::blockStatus() const {
    std::list<SizedObjectData> blockPositions;
    std::ranges::transform(terrainBlocks, std::back_inserter(blockPositions),
                           [](const TerrainBlock* block) { return block->status(); });
    return blockPositions;
}

std::list<SizedObjectData> Level::itemSpawnerStatus() const {
    std::list<SizedObjectData> itemPositions;
    std::ranges::transform(itemSpawners, std::back_inserter(itemPositions),
                           [](const ItemSpawner* itemSpawner) { return itemSpawner->status(); });
    return itemPositions;
}

std::list<SizedObjectData> Level::boxStatus() const {
    std::list<SizedObjectData> boxPositions;
    std::ranges::transform(boxes, std::back_inserter(boxPositions),
                           [](const Box* box) { return box->status(); });
    return boxPositions;
}

std::list<SizedObjectData> Level::explosionStatus() const {
    std::list<SizedObjectData> explosionPositions;
    std::ranges::transform(explosions, std::back_inserter(explosionPositions),
                           [](const Explosion* explosion) { return explosion->status(); });
    return explosionPositions;
}

Level::~Level() = default;
