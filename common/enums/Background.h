#pragma once

#include <string>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

#include "Types.h"

struct BackgroundID {
    enum Value : u8 {
        CascadeCave = 0,
        City = 1,
        DarkCave = 2,
        Desert = 3,
        ForestDay = 4,
        ForestNight = 5,
        SnowyPeaks = 6,
        Sunset = 7
    };

    /**
     * Construct a background id with the given value
     * @param value The value of the background id
     */
    // cppcheck-suppress noExplicitConstructor
    BackgroundID(Value value);

    /**
     * Cast the background id to its value
     * @return The value of the background id
     */
    // cppcheck-suppress noExplicitConstructor
    operator Value() const;

    /**
     * Get the path in the resource folder of the given background
     * @return The path to the background image
     */
    const std::string& pathToBackground() const;

    /**
     * Get the path in the resource folder of the given tileset
     * @return The path to the tileset image
     */
    const std::string& pathToTileset() const;


private:
    const static HashMap<BackgroundID, std::string> backgrounds;
    const static HashMap<BackgroundID, std::string> tilesets;
    friend struct std::hash<BackgroundID>;
    friend struct std::equal_to<BackgroundID>;

    Value value;
};

template <>
struct std::hash<BackgroundID> {
    std::size_t operator()(const BackgroundID& id) const noexcept {
        return std::hash<BackgroundID::Value>()(id.value);
    }
};

template <>
struct std::equal_to<BackgroundID> {
    bool operator()(const BackgroundID& lhs, const BackgroundID& rhs) const {
        return lhs.value == rhs.value;
    }
};

template <>
struct YAML::convert<BackgroundID> {
    static bool decode(const Node& node, BackgroundID& rhs) {
        rhs = BackgroundID(node.as<BackgroundID::Value>());
        return true;
    }

    static Node encode(const BackgroundID& rhs) { return Node(rhs); }
};
