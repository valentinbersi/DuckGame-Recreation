#pragma once

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <utility>
#include <QMetaType>

enum ObjectType {
    PLATFORM,
    DUCK,
    GUN,
    BOX
};

struct Object {
    ObjectType type;
    int height;
    int width;
    QString icon;
    int pos_x;
    int pos_y;

    Object(ObjectType type, int height, int width, QString icon)
            : type(type),
            height(height),
            width(width),
            icon(std::move(icon)),
            pos_x(0), pos_y(0) {}

    void setPos(int x, int y) {
        pos_x = x;
        pos_y = y;
    }
};

Q_DECLARE_METATYPE(Object*)
