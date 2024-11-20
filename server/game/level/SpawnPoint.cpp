#include "SpawnPoint.h"

#include <utility>

SpawnPoint::SpawnPoint(Vector2 position): GameObject2D(nullptr, std::move(position)) {}
