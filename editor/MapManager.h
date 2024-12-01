#pragma once

#include <list>
#include <string>

#include "MapData.h"
#include "Object.h"

class MapManager {
private:
    static std::string objectTypeToString(ObjectType type);
    static ObjectType stringToObjectType(const std::string& typeStr);
    static void addOffset(MapData& mapData);

public:
    MapManager() = default;

    static void exportMap(MapData& mapData);
    static bool importMap(MapData& mapData);
};
