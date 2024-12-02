#pragma once

#include <string>
#include <unordered_map>

enum class BackgroundID {
    CASCADE_CAVE = 0,
    CITY = 1,
    DARK_CAVE = 2,
    DESERT = 3,
    FOREST_DAY = 4,
    FOREST_NIGHT = 5,
    SNOWY_PEAKS = 6,
    SUNSET = 7
};

const static std::unordered_map<BackgroundID, std::string> backgrounds;
