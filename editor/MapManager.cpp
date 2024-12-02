#include "MapManager.h"

#include <QDebug>
#include <fstream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "Background.h"

/** la unidad de los offset son pixeles. 2 Pixeles == 1 Tile */
/** Se agrega un borde de 40 tiles por encima y por debajo del mapa y de 20 tiles a los costados */
#define OFFSET_UP 80
#define OFFSET_DOWN 80
#define OFFSET_RIGHT 40
#define OFFSET_LEFT 40

MapManager::MapManager(MapData& mapData): mapData(mapData) {}

void MapManager::addOffset() {
    int x_min = mapData.width;
    int x_max = 0;
    int y_min = mapData.height;
    int y_max = 0;

    // busco los máximos y mínimos.
    for (Object& obj: mapData.objects) {
        QPointF topLeftPos = obj.getBoundingPos();
        if (topLeftPos.x() < x_min)
            x_min = (int)topLeftPos.x();
        if (topLeftPos.y() < y_min)
            y_min = (int)topLeftPos.y();
        QPointF bottomRightPos(topLeftPos.x() + obj.size.width(),
                               topLeftPos.y() + obj.size.height());
        if (bottomRightPos.x() > x_max)
            x_max = (int)bottomRightPos.x();
        if (bottomRightPos.y() > y_max)
            y_max = (int)bottomRightPos.y();
    }

    // calculo los offsets
    int offsetUp = OFFSET_UP;
    if (y_min < OFFSET_UP)
        offsetUp -= y_min;
    if (y_min > OFFSET_UP)
        offsetUp = 0;

    int offsetLeft = OFFSET_LEFT;
    if (x_min < OFFSET_LEFT)
        offsetLeft -= x_min;
    if (x_min > OFFSET_LEFT)
        offsetLeft = 0;

    //    int offsetDown = OFFSET_DOWN;
    //    if (mapData.height - y_max < OFFSET_DOWN)
    //        offsetDown = OFFSET_DOWN - (mapData.height - y_max);
    //
    //    int offsetRight = OFFSET_RIGHT;
    //    if (mapData.width - x_max < OFFSET_RIGHT)
    //        offsetRight = OFFSET_RIGHT - (mapData.width - x_max);

    // ajusto el tamaño del mapa
    mapData.width = offsetLeft + x_max + OFFSET_RIGHT;
    mapData.height = offsetUp + y_max + OFFSET_DOWN;

    // muevo los objetos
    QPoint offsetObject(offsetLeft, offsetUp);
    for (Object& obj: mapData.objects) {
        obj.centerPos += offsetObject;
    }
}

void MapManager::exportMap() {
    //    std::string path = "maps/" + mapData.name + ".yaml";
    //    std::ofstream fout(path);
    addOffset();
    mapData.path = "maps/" + mapData.name + ".yaml";
    std::ofstream fout(mapData.path);
    if (!fout.is_open()) {
        qWarning() << "Could not open save file";
        return;
    }

    YAML::Node mapNode;

    mapNode["map_name"] = mapData.name;
    mapNode["background"] = (int)mapData.backgroundID;
    mapNode["map_width"] = mapData.width;
    mapNode["map_height"] = mapData.height;

    YAML::Node objectsNode(YAML::NodeType::Sequence);
    for (const auto& obj: mapData.objects) {
        YAML::Node objNode;
        objNode["type"] = objectTypeToString(obj.type);
        objNode["x"] = obj.centerPos.x();
        objNode["y"] = obj.centerPos.y();
        objectsNode.push_back(objNode);
    }

    mapNode["objects"] = objectsNode;

    fout << mapNode;
    fout.close();
    qDebug() << "se guardo el mapa";
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

bool MapManager::importMap() {
    std::ifstream fin(mapData.path);
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

        mapData.name = mapNode["map_name"].as<std::string>();
        mapData.width = mapNode["map_width"].as<int>();
        mapData.height = mapNode["map_height"].as<int>();
        mapData.backgroundID = (BackgroundID)((BackgroundID::Value)(mapNode["background"].as<int>()));
        qDebug() << "tamaño del mapa:" << mapData.width << mapData.height;
        YAML::Node objectsNode = mapNode["objects"];
        for (const auto& objNode: objectsNode) {
            auto typeStr = objNode["type"].as<std::string>();
            Object object(stringToObjectType(typeStr));

            object.centerPos.setX(objNode["x"].as<int>());
            object.centerPos.setY(objNode["y"].as<int>());

            mapData.objects.push_back(object);
        }
    } catch (const YAML::Exception& e) {
        qWarning() << "Error reading YAML file: " << e.what();
    }

    fin.close();
    return true;
}
