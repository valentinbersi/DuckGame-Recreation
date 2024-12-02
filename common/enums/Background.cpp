#include "Background.h"

BackgroundID::BackgroundID(const Value value): value(value) {}

BackgroundID::operator Value() const { return value; }

const std::string& BackgroundID::path() const { return backgrounds.at(*this); }

const HashMap<BackgroundID, std::string> backgrounds = {
        {BackgroundID::CascadeCave, "assets/backgrounds/cascade_cave.png"},
        {BackgroundID::City, "assets/backgrounds/city.png"},
        {BackgroundID::DarkCave, "assets/backgrounds/dark_cave.png"},
        {BackgroundID::Desert, "assets/backgrounds/desert.png"},
        {BackgroundID::ForestDay, "assets/backgrounds/forest_day.png"},
        {BackgroundID::ForestNight, "assets/backgrounds/forest_night.png"},
        {BackgroundID::SnowyPeaks, "assets/backgrounds/snowy_peaks.png"},
        {BackgroundID::Sunset, "assets/backgrounds/sunset.png"}};
