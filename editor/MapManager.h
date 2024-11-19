#pragma once

#include "yaml-cpp/yaml.h"
#include "Object.h"
#include <vector>

class MapManager {
public:
    MapManager() = default;

    static void exportMap(const std::vector<Object>& objects, const std::string& mapName, int mapWidth, int mapHeight);
    static bool importMap(std::vector<Object>& objects, const std::string& mapName, int& mapWidth,
                   int& mapHeight, std::string& background);
private:
    static std::string objectTypeToString(ObjectType type);
    static ObjectType stringToObjectType(const std::string& typeStr);

};
