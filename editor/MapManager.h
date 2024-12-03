#pragma once

#include <list>
#include <string>

#include "MapData.h"
#include "Object.h"

class MapManager {
private:
    MapData& mapData;

    void addOffset() const;

    void removeOffset() const;

public:
    explicit MapManager(MapData& mapData);

    /**
    * Se encarga de exportar el mapa en formato YAML.
    * Toma la informacion del mapa (name, background, size y objects) y las configura en el .yaml
    * Le da la posibilidad al usuario de elegir donde guardar el archivo
    */
    bool exportMap(QWidget* view) const;

    /**
    * Se encarga de importar un mapa desde el formato YAML.
    * Toma la informacion del .yaml (name, background, size y objects) y los carga en mapData
    * Le da la posibilidad al usuario de elegir que archivo cargar
    */
    bool importMap(QWidget* view) const;
};
