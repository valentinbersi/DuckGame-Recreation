#pragma once
#include "StaticObject.h"

/**
 * A platform in the game
 */
class Platform final: public StaticObject {
public:
    Platform();

    void start() override;
    void update(float delta) override;
    GameStatus status() override;
};
