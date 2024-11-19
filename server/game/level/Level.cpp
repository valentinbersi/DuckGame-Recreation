#include "Level.h"

#include <iostream>

#include <yaml-cpp/yaml.h>

Level Level::load(const std::string& name) {
    YAML::Node level = YAML::LoadFile("maps/" + name + ".yaml");

    std::cout << "Map width: " << level["map_width"].as<int>() << std::endl;
    std::cout << "Map height: " << level["map_height"].as<int>() << std::endl;
    std::cout << "Terrain blocks: " << level["objects"].size() << std::endl;

    for (const YAML::Node& object: level["objects"].as<std::vector<YAML::Node>>())
        std::cout << "Block of type:" << object["type"].as<std::string>() << " at ("
                  << object["x"].as<float>() << ", " << object["y"].as<float>() << ")" << std::endl;

    return {};
}