#pragma once

#include <fstream>
#include <list>

#include "Types.h"
#include "Vector2.h"

struct Level {
    std::list<Vector2> terrainBlocks;
    std::list<Vector2> duckSpawnPoints;
    std::list<Vector2> boxes;
    std::list<Vector2> gunSpawnPoints;
    u64 width, height;

    static Level load(const std::string& name);
};
