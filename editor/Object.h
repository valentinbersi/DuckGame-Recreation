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
    ARMAMENT,
    BOX,
    UNKNOWN // objeto invalido
};

struct Object {
    ObjectType type;
    QString icon;
    QPointF centerPos;
    QSize size;

    Object(ObjectType type, int height, int width, QString icon)
            : type(type),
            icon(std::move(icon)),
            size(width, height){}

//    void setPos(int x, int y) {
//        pos_x = x;
//        pos_y = y;
//        qDebug() << "la posicion del objecto de tipo" << type << "es (" << pos_x << "," << pos_y << ")";
//    }

    void setCenterPosition(QPointF center) {
        centerPos = center;
    }

    QRectF getBoundingPos() {
        return QRectF {
        centerPos.x() - size.width()/2,
        centerPos.y() - size.height()/2,
        static_cast<qreal>(size.width()),
        static_cast<qreal>(size.height())
        };
    }
};

Q_DECLARE_METATYPE(Object*)
