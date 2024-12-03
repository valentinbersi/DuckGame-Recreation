#include "TerrainBlock.h"

#include <utility>

#define BLOCK_DIMENSIONS 2, 2

TerrainBlock::TerrainBlock(Vector2 position):
        StaticObject(std::move(position), 2, 0, BLOCK_DIMENSIONS) {}

SizedObjectData TerrainBlock::status() const { return {position(), BLOCK_DIMENSIONS}; }
