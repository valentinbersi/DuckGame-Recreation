#pragma once

#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "Object.h"

class MapManager {
private:
    static std::string objectTypeToString(ObjectType type);
    static ObjectType stringToObjectType(const std::string& typeStr);

public:
    MapManager() = default;

    static void exportMap(const std::vector<Object>& objects, const std::string& mapName,
                          int mapWidth, int mapHeight);
    static bool importMap(std::vector<Object>& objects, const std::string& mapName, int& mapWidth,
                          int& mapHeight, std::string& background);
};
