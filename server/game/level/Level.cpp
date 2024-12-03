#include "Level.h"

#include <algorithm>
#include <list>

#include "ItemSpawner.h"
#include "Layer.h"
#include "SpawnPoint.h"
#include "TerrainBlock.h"

#define eventHandler(Function, ...) \
    gameObject::EventHandler<Level, __VA_ARGS__>::create(getReference<Level>(), Function)

void Level::onTreeExited(GameObject* object) {
    if (const auto box = dynamic_cast<Box*>(object); box != nullptr) {
        boxes.remove(box);
    }
}

Level::Level(const LevelData& level, const HashMap<u16, Player*>& players) {
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

void Level::update([[maybe_unused]] float delta) {
    std::vector<Box*> boxesToDestroy;
    boxes.remove_if([&boxesToDestroy](Box* box) {
        if (box->wasDestroyed()) {
            boxesToDestroy.push_back(box);
            return true;
        }
        return false;
    });

    for (Box* box: boxesToDestroy) removeChild(box);
}

Level::~Level() = default;
