#include "MapManager.h"

#include <QDebug>
#include <fstream>
#include <list>
#include <string>

#include "yaml-cpp/yaml.h"

void MapManager::exportMap(const std::list<Object>& objects, const std::string& mapName,
                           int mapWidth, int mapHeight, const std::string& background) {
    std::string path = "maps/" + mapName + ".yaml";
    std::ofstream fout(path);
    if (!fout.is_open()) {
        qWarning() << "Could not open save file";
        return;
    }

    YAML::Node mapNode;

    mapNode["map_name"] = mapName;
    mapNode["background"] = background;
    mapNode["map_width"] = mapWidth;
    mapNode["map_height"] = mapHeight;

    YAML::Node objectsNode(YAML::NodeType::Sequence);
    for (const auto& obj: objects) {
        YAML::Node objNode;
        objNode["type"] = objectTypeToString(obj.type);
        objNode["x"] = obj.centerPos.x();
        objNode["y"] = obj.centerPos.y();
        objectsNode.push_back(objNode);
    }

    mapNode["objects"] = objectsNode;

    fout << mapNode;
    fout.close();
}

std::string MapManager::objectTypeToString(ObjectType type) {
    if (type == PLATFORM)
        return "PLATFORM";
    if (type == DUCK)
        return "DUCK";
    if (type == ARMAMENT)
        return "ARMAMENT";
    if (type == BOX)
        return "BOX";
    return "UNKNOWN";
}

ObjectType MapManager::stringToObjectType(const std::string& typeStr) {
    if (typeStr == "PLATFORM")
        return PLATFORM;
    if (typeStr == "DUCK")
        return DUCK;
    if (typeStr == "ARMAMENT")
        return ARMAMENT;
    if (typeStr == "BOX")
        return BOX;
    return UNKNOWN;
}

bool MapManager::importMap(std::list<Object>& objects, const std::string& mapPath, int& mapWidth,
                           int& mapHeight, std::string& background) {
    std::ifstream fin(mapPath);
    if (!fin.is_open()) {
        qWarning() << "Could not open the file to load the map.";
        return false;
    }

    try {
        YAML::Node mapNode = YAML::Load(fin);
        if (!mapNode["map_name"] || !mapNode["background"] || !mapNode["map_width"] ||
            !mapNode["map_height"] || !mapNode["objects"]) {
            qWarning() << "The map file is not in the expected format.";
            return false;
        }

        auto mapNameFromFile = mapNode["map_name"].as<std::string>();
        mapWidth = mapNode["map_width"].as<int>();
        mapHeight = mapNode["map_height"].as<int>();
        background = mapNode["background"].as<std::string>();

        YAML::Node objectsNode = mapNode["objects"];
        for (const auto& objNode: objectsNode) {
            auto typeStr = objNode["type"].as<std::string>();
            Object object(stringToObjectType(typeStr));

            object.centerPos.setX(objNode["x"].as<int>());
            object.centerPos.setY(objNode["y"].as<int>());

            objects.push_back(object);
        }
    } catch (const YAML::Exception& e) {
        qWarning() << "Error reading YAML file: " << e.what();
    }

    fin.close();
    return true;
}
