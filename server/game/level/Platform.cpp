#include "Platform.h"

Platform::Platform(Vector2 position, const float width, const float height):
        StaticObject(nullptr, std::move(position), 2, 0, width, height) {}

void Platform::start() {}

void Platform::update([[maybe_unused]] float delta) {}

GameStatus Platform::status() { return GameStatus{}; }