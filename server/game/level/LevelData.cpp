#include "LevelData.h"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

std::vector<LevelData> LevelData::loadLevels() {
    std::vector<LevelData> levels;

    if (not std::filesystem::exists("maps/") or not std::filesystem::is_directory("maps/"))
        throw std::logic_error("The maps directory does not exist.");

    for (const auto& entry: std::filesystem::directory_iterator("maps/")) {
        if (not entry.is_regular_file() or entry.path().extension() != ".yaml")
            continue;

        if (const std::optional<LevelData> level = load(entry.path().string()))
            levels.emplace_back(level.value());
    }

    return levels;
}

#define MIN_SPAWN_POINTS 4

#define WIDTH "map_width"
#define HEIGHT "map_height"
#define OBJECTS "objects"
#define TYPE "type"
#define PLATFORM "PLATFORM"
#define X_COORD "x"
#define Y_COORD "y"
#define DUCK "DUCK"
#define BOX "BOX"
#define ARMAMENT "ARMARMAMENT"

std::optional<LevelData> LevelData::load(const std::string& path) {
    YAML::Node level = YAML::LoadFile(path);
    LevelData loadedLevel;

    loadedLevel.width = level[WIDTH].as<u64>();
    loadedLevel.height = level[HEIGHT].as<u64>();

    for (const YAML::Node& object: level[OBJECTS].as<std::vector<YAML::Node>>())
        if (object[TYPE].as<std::string>() == PLATFORM)
            loadedLevel.terrainBlocks.emplace_back(object[X_COORD].as<float>(),
                                                   object[Y_COORD].as<float>());

        else if (object[TYPE].as<std::string>() == DUCK)
            loadedLevel.duckSpawnPoints.emplace_back(object[X_COORD].as<float>(),
                                                     object[Y_COORD].as<float>());

        else if (object[TYPE].as<std::string>() == BOX)
            loadedLevel.boxes.emplace_back(object[X_COORD].as<float>(),
                                           object[Y_COORD].as<float>());

        else if (object[TYPE].as<std::string>() == ARMAMENT)
            loadedLevel.gunSpawnPoints.emplace_back(object[X_COORD].as<float>(),
                                                    object[Y_COORD].as<float>());

    if (loadedLevel.duckSpawnPoints.size() < MIN_SPAWN_POINTS)
        return std::nullopt;

    return loadedLevel;
}
