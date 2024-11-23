#include "LevelData.h"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#define MAPS_DIRECTORY "maps/"
#define MAP_DIRECTORY_NOT_FOUND "The maps directory does not exist."
#define YAML_EXTENSION ".yaml"
#define NO_LEVELS "No levels found"

std::vector<LevelData> LevelData::loadLevels() {
    std::vector<LevelData> levels;

    if (not std::filesystem::exists(MAPS_DIRECTORY) or
        not std::filesystem::is_directory(MAPS_DIRECTORY))
        throw std::logic_error(MAP_DIRECTORY_NOT_FOUND);

    for (const auto& entry: std::filesystem::directory_iterator(MAPS_DIRECTORY)) {
        if (not entry.is_regular_file() or entry.path().extension() != YAML_EXTENSION)
            continue;

        std::optional level(load(entry.path().string()));

        if (not level)
            continue;

        levels.emplace_back(std::move(level.value()));
    }

    if (levels.empty())
        throw std::logic_error(NO_LEVELS);

    return levels;
}

#define WIDTH "map_width"
#define HEIGHT "map_height"
#define OBJECTS "objects"
#define PLATFORM "PLATFORM"
#define DUCK "DUCK"
#define BOX "BOX"
#define ARMAMENT "ARMAMENT"
#define TYPE "type"
#define X_COORD "x"
#define Y_COORD "y"
#define MIN_SPAWN_POINTS 4

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
            loadedLevel.itemSpawnPoints.emplace_back(object[X_COORD].as<float>(),
                                                     object[Y_COORD].as<float>());

    if (loadedLevel.duckSpawnPoints.size() < MIN_SPAWN_POINTS)
        return std::nullopt;

    return loadedLevel;
}
