#include "MapExporter.h"

#include <QDebug>
#include <fstream>

void MapExporter::exportMap(const std::vector<Object>& objects, const std::string& mapName, int mapWidth, int mapHeight){
    std::string path = "../maps/" + mapName + ".yaml";
    std::ofstream fout(path);
    if (!fout.is_open()) {
        qWarning() << "No se pudo abrir el archivo para guardar.";
        return;
    }

    YAML::Node mapNode;

    mapNode["map_name"] = mapName;
    mapNode["background"] = "background_image.png";
    mapNode["map_width"] = mapWidth;
    mapNode["map_height"] = mapHeight;

    YAML::Node objectsNode(YAML::NodeType::Sequence);
    for (const auto& obj : objects) {
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

std::string MapExporter::objectTypeToString(ObjectType type) {
    switch (type) {
        case PLATFORM: return "PLATFORM";
        case DUCK: return "DUCK";
        case ARMAMENT: return "ARMAMENT";
        case BOX: return "BOX";
        default: return "UNKNOWN";
    }
}