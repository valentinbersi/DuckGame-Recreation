#include "Ray2D.h"

#include <utility>

Ray2D::Ray2D(Vector2 origin, Vector2 direction):
        _origin(std::move(origin)), _direction(std::move(direction)) {}

Vector2 Ray2D::origin() const { return _origin; }

void Ray2D::setOrigin(Vector2 origin) { this->_origin = std::move(origin); }

Vector2 Ray2D::direction() const { return _direction; }

void Ray2D::setDirection(Vector2 direction) { this->_direction = std::move(direction); }
