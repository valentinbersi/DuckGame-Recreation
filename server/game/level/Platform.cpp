#include "Platform.h"

Platform::Platform(): StaticObject(nullptr, {0, 600}, 2, 0, 800, 200) {}

void Platform::start() {}

void Platform::update([[maybe_unused]] float delta) {}

GameStatus Platform::status() { return GameStatus{}; }