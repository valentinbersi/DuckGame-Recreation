#pragma once

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <utility>
#include <QMetaType>

#include <QDebug>

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
        qDebug() << "la posicion del objecto de tipo" << type << "es (" << pos_x << "," << pos_y << ")";
    }
};

Q_DECLARE_METATYPE(Object*)
