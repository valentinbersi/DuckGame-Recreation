#pragma once

#include "GameObject2D.h"

class SpawnPoint final: public GameObject2D {
public:
    explicit SpawnPoint(Vector2 position);
};
