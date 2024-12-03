#pragma once

#include <list>
#include <string>

#include "MapData.h"
#include "Object.h"

class MapManager {
private:
    MapData& mapData;

    std::string objectTypeToString(ObjectType type);
    ObjectType stringToObjectType(const std::string& typeStr);
    void addOffset() const;

public:
    explicit MapManager(MapData& mapData);

    bool exportMap(QWidget* view);
    bool importMap();
};
