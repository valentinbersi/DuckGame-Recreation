#pragma once

#include <list>
#include <string>

#include "Object.h"

struct MapData {
    std::string name;
    std::string path;
    std::string backgroundPath;
    int width;
    int height;
    std::list<Object> objects;
};
