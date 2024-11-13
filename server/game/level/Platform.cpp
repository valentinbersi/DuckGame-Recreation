#include "Platform.h"

#include "Rectangle.h"

Platform::Platform():
        StaticObject(nullptr, {0, 400}, 2, 0,
                     std::make_unique<Rectangle>(Vector2(0, 0), 1000, 80)) {}
void Platform::start() {}

void Platform::update([[maybe_unused]] float delta) {}

GameStatus Platform::status() { return GameStatus{}; }