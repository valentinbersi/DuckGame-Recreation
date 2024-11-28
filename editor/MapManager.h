#pragma once

#include <list>
#include <string>

#include "Object.h"

class MapManager {
private:
    static std::string objectTypeToString(ObjectType type);
    static ObjectType stringToObjectType(const std::string& typeStr);

public:
    MapManager() = default;

    static void exportMap(const std::list<Object>& objects, const std::string& mapName,
                          int mapWidth, int mapHeight, const std::string& background);
    static bool importMap(std::list<Object>& objects, const std::string& mapName, int& mapWidth,
                          int& mapHeight, const std::string& background);
};
