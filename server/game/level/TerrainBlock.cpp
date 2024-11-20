#include "TerrainBlock.h"

#include <utility>

TerrainBlock::TerrainBlock(Vector2 position):
        StaticObject(nullptr, std::move(position), 2, 0, 2, 2) {}

void TerrainBlock::start() {}

void TerrainBlock::update([[maybe_unused]] float delta) {}
