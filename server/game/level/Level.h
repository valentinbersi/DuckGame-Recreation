#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "Vector2.h"

struct Level {
    std::vector<Vector2> terrainBlocks;
    std::vector<Vector2> duckSpawnPoints;
    std::vector<Vector2> boxes;
    std::vector<Vector2> gunSpawnPoints;
    u64 width, height;

    static std::vector<Level> loadLevels();

private:
    /**
     * Load a level from a file.
     * @param fileName The name of the file to load.
     * @return The loaded level.
     */
    static Level load(const std::string& path);
};
