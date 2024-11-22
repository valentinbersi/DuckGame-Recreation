#pragma once

#include "SizedObjectData.h"
#include "StaticObject.h"

/**
 * A platform in the game
 */
class TerrainBlock final: public StaticObject {
public:
    explicit TerrainBlock(Vector2 position);

    void start() override;
    void update(float delta) override;

    SizedObjectData status();
};
