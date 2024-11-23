#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "Vector2.h"

struct LevelData final {
    std::vector<Vector2> terrainBlocks;
    std::vector<Vector2> duckSpawnPoints;
    std::vector<Vector2> boxes;
    std::vector<Vector2> itemSpawnPoints;
    u64 width, height;

    /**
     * Load all levels from the maps directory.
     * @return  A vector of all loaded levels.
     */
    static std::vector<LevelData> loadLevels();

private:
    /**
     * Load a level from a file.
     * @param path The path to the file.
     * @return The loaded level.
     */
    static LevelData load(const std::string& path);
};
