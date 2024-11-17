#pragma once

#include "yaml-cpp/yaml.h"
#include "Object.h"
#include <vector>

class MapExporter {
public:
    MapExporter() = default;

    static void exportMap(const std::vector<Object>& objects, const std::string& mapName, int mapWidth, int mapHeight);

private:
    static std::string objectTypeToString(ObjectType type);
};
