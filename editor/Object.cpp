#include "Object.h"

#include <string>

Object::Object(ObjectType type): type(type) {
    if (type == PLATFORM) {
        iconPath = PLATFORM_ICON;
        size = QSize(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    } else if (type == DUCK) {
        iconPath = DUCK_ICON;
        size = QSize(DUCK_WIDTH, DUCK_HEIGHT);
    } else if (type == ARMAMENT) {
        iconPath = ARMAMENT_ICON;
        size = QSize(SPAWN_WIDTH, SPAWN_HEIGHT);
    } else if (type == BOX) {
        iconPath = BOX_ICON;
        size = QSize(BOX_WIDTH, BOX_HEIGHT);
    } else {
        qWarning() << "Tipo de objeto desconocido";
        iconPath = "";
        size = QSize(0, 0);
    }

    QPixmap i(iconPath);
    icon = i.scaled(PIXEL_SIZE * size.width(), PIXEL_SIZE * size.height(), Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation);
}

Object::Object(): type(UNKNOWN), size(0, 0), centerPos(0, 0), icon(QPixmap()) {}

void Object::setCenterPosition(QPointF pos, bool isTopLeftPos) {
    if (isTopLeftPos)
        centerPos = QPointF(pos.x() + size.width() / 2.0, pos.y() + size.height() / 2.0);
    else
        centerPos = pos;
}

QPointF Object::getBoundingPos() const {
    return QPointF(centerPos.x() - size.width() / 2.0, centerPos.y() - size.height() / 2.0);
}

bool Object::operator==(const Object& other) const {
    return type == other.type && iconPath == other.iconPath && size == other.size &&
           centerPos == other.centerPos;
}

std::string Object::objectTypeToString(ObjectType type) {
    switch (type) {
        case PLATFORM:
            return "PLATFORM";
        case DUCK:
            return "DUCK";
        case ARMAMENT:
            return "ARMAMENT";
        case BOX:
            return "BOX";
        default:
            return "UNKNOWN";
    }
}

ObjectType Object::stringToObjectType(const std::string& typeStr) {
    if (typeStr == "PLATFORM")
        return PLATFORM;
    if (typeStr == "DUCK")
        return DUCK;
    if (typeStr == "ARMAMENT")
        return ARMAMENT;
    if (typeStr == "BOX")
        return BOX;
    return UNKNOWN;
}
