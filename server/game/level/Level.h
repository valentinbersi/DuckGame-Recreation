#pragma once

#include <fstream>
#include <list>

#include "Types.h"
#include "Vector2.h"

struct Level {
    std::vector<Vector2> terrainBlocks;
    std::vector<Vector2> duckSpawnPoints;
    std::vector<Vector2> boxes;
    std::vector<Vector2> gunSpawnPoints;
    u64 width, height;

    static Level load(const std::string& name);
};
