#pragma once

#include <fstream>
#include <list>

#include "SpawnPoint.h"
#include "TerrainBlock.h"

class Level {
    std::list<TerrainBlock> terrainBlocks;
    std::list<SpawnPoint> spawnPoints;

public:
    static Level load(const std::string& name);
};
