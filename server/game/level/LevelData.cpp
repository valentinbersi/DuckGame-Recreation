#include "LevelData.h"

#include <filesystem>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

std::vector<LevelData> LevelData::loadLevels() {
    std::vector<LevelData> levels;

    if (not std::filesystem::exists("maps/") or not std::filesystem::is_directory("maps/"))
        throw std::logic_error("The maps directory does not exist.");

    for (const auto& entry: std::filesystem::directory_iterator("maps/")) {
        if (entry.is_regular_file() and entry.path().extension() == ".yaml")
            levels.emplace_back(load(entry.path().string()));
    }

    return levels;
}

LevelData LevelData::load(const std::string& path) {
    YAML::Node level = YAML::LoadFile(path);
    LevelData loadedLevel;

    loadedLevel.width = level["map_width"].as<u64>();
    loadedLevel.height = level["map_height"].as<u64>();

    for (const YAML::Node& object: level["objects"].as<std::vector<YAML::Node>>())
        if (object["type"].as<std::string>() == "PLATFORM")
            loadedLevel.terrainBlocks.emplace_back(object["x"].as<float>(),
                                                   object["y"].as<float>());
        else if (object["type"].as<std::string>() == "DUCK")
            loadedLevel.duckSpawnPoints.emplace_back(object["x"].as<float>(),
                                                     object["y"].as<float>());
        else if (object["type"].as<std::string>() == "BOX")
            loadedLevel.boxes.emplace_back(object["x"].as<float>(), object["y"].as<float>());
        else if (object["type"].as<std::string>() == "ARMAMENT")
            loadedLevel.itemSpawnPoints.emplace_back(object["x"].as<float>(),
                                                    object["y"].as<float>());

    return loadedLevel;
}
