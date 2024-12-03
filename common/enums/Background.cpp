#include "Background.h"

BackgroundID::BackgroundID(): value(None) {}

BackgroundID::BackgroundID(const Value value): value(value) {}

BackgroundID::operator Value() const { return value; }

const std::string& BackgroundID::pathToBackground() const { return backgrounds.at(*this); }

const std::string& BackgroundID::pathToTileset() const { return tilesets.at(*this); }

const HashMap<BackgroundID, std::string> BackgroundID::backgrounds = {
        {BackgroundID::CascadeCave, "background/cascade-cave.png"},
        {BackgroundID::City, "background/city.png"},
        {BackgroundID::DarkCave, "background/dark-cave.png"},
        {BackgroundID::Desert, "background/desert.png"},
        {BackgroundID::ForestDay, "background/forest-day.png"},
        {BackgroundID::ForestNight, "background/forest-night.png"},
        {BackgroundID::SnowyPeaks, "background/snowy-peaks.png"},
        {BackgroundID::Sunset, "background/sunset.png"}};

const HashMap<BackgroundID, std::string> BackgroundID::tilesets = {
        {BackgroundID::CascadeCave, "tilesets/cascade-cave.png"},
        {BackgroundID::City, "tilesets/city.png"},
        {BackgroundID::DarkCave, "tilesets/dark-cave.png"},
        {BackgroundID::Desert, "tilesets/desert.png"},
        {BackgroundID::ForestDay, "tilesets/forest-day.png"},
        {BackgroundID::ForestNight, "tilesets/forest-night.png"},
        {BackgroundID::SnowyPeaks, "tilesets/snowy-peaks.png"},
        {BackgroundID::Sunset, "tilesets/sunset.png"}};
