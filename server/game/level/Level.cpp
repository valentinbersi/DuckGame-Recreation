#include "Level.h"

#include <yaml-cpp/yaml.h>

Level Level::load(const std::string& name) {
    YAML::Node level = YAML::LoadFile("maps/" + name + ".yaml");
    Level loadedLevel;

    loadedLevel.width = level["map_width"].as<u64>();
    loadedLevel.height = level["map_height"].as<u64>();

    for (const YAML::Node& object: level["objects"].as<std::vector<YAML::Node>>)
        if (object["type"].as<std::string>() == "PLATFORM")
            loadedLevel.terrainBlocks.emplace_back(object["x"].as<float>(),
                                                   object["y"].as<float>());
        else if (object["type"].as<std::string>() == "DUCK")
            loadedLevel.duckSpawnPoints.emplace_back(object["x"].as<float>(),
                                                     object["y"].as<float>());
        else if (object["type"].as<std::string>() == "BOX")
            loadedLevel.boxes.emplace_back(object["x"].as<float>(), object["y"].as<float>());
        else if (object["type"].as<std::string>() == "ARMAMENT")
            loadedLevel.gunSpawnPoints.emplace_back(object["x"].as<float>(),
                                                    object["y"].as<float>());

    if (loadedLevel.duckSpawnPoints.empty())
        throw std::runtime_error("No duck spawn points in the level");

    return loadedLevel;
}