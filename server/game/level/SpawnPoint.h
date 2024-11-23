#pragma once

#include "GameObject2D.h"

class SpawnPoint final: public GameObject2D {
public:
    /**
     * Creates a new SpawnPoint
     * @param position the position of the SpawnPoint
     */
    explicit SpawnPoint(Vector2 position);
};
