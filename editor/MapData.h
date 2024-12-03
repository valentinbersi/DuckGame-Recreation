#pragma once

#include <list>
#include <string>

#include "Background.h"
#include "Object.h"

struct MapData {
    std::string name;
    std::string path;
    BackgroundID backgroundID = BackgroundID(BackgroundID::CascadeCave);
    int width;
    int height;
    std::list<Object> objects;
};
