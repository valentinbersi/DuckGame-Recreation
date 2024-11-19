#pragma once
#include "StaticObject.h"

/**
 * A platform in the game
 */
class Platform final: public StaticObject {
public:
    Platform(Vector2 position, float width, float height);

    void start() override;
    void update(float delta) override;
    GameStatus status() override;
};
