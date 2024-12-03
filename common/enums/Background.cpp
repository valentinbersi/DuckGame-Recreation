#include "Background.h"

BackgroundID::BackgroundID(const Value value): value(value) {}

BackgroundID::operator Value() const { return value; }

const std::string& BackgroundID::path() const { return backgrounds.at(*this); }

const HashMap<BackgroundID, std::string> BackgroundID::backgrounds = {
        {BackgroundID::CascadeCave, "background/cascade-cave.png"},
        {BackgroundID::City, "background/city.png"},
        {BackgroundID::DarkCave, "background/dark-cave.png"},
        {BackgroundID::Desert, "background/desert.png"},
        {BackgroundID::ForestDay, "background/forest-day.png"},
        {BackgroundID::ForestNight, "background/forest-night.png"},
        {BackgroundID::SnowyPeaks, "background/snowy-peaks.png"},
        {BackgroundID::Sunset, "background/sunset.png"}};
