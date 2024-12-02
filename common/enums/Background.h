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

const std::unordered_map<BackgroundID, std::string> backgrounds = {
        {BackgroundID::CASCADE_CAVE, "assets/backgrounds/cascade_cave.png"},
        {BackgroundID::CITY, "assets/backgrounds/city.png"},
        {BackgroundID::DARK_CAVE, "assets/backgrounds/dark_cave.png"},
        {BackgroundID::DESERT, "assets/backgrounds/desert.png"},
        {BackgroundID::FOREST_DAY, "assets/backgrounds/forest_day.png"},
        {BackgroundID::FOREST_NIGHT, "assets/backgrounds/forest_night.png"},
        {BackgroundID::SNOWY_PEAKS, "assets/backgrounds/snowy_peaks.png"},
        {BackgroundID::SUNSET, "assets/backgrounds/sunset.png"}
};
