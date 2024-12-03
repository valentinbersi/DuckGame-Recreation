#pragma once

#include <list>
#include <string>

#include "MapData.h"
#include "Object.h"

class MapManager {
private:
    MapData& mapData;

    void addOffset() const;

public:
    explicit MapManager(MapData& mapData);

    bool exportMap(QWidget* view) const;

    void removeOffset() const;

    bool importMap(QWidget* view) const;
};
