#include "TerrainBlock.h"

#include <utility>

#define BLOCK_DIMENSIONS 2, 2

TerrainBlock::TerrainBlock(Vector2 position):
        StaticObject(nullptr, std::move(position), 2, 0, BLOCK_DIMENSIONS) {}

void TerrainBlock::start() {}

void TerrainBlock::update([[maybe_unused]] float delta) {}

SizedObjectData TerrainBlock::status() { return {position(), BLOCK_DIMENSIONS}; }
