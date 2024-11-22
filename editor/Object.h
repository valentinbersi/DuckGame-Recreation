#pragma once

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <utility>

#include "EditorConstants.h"

enum ObjectType {
    PLATFORM,
    DUCK,
    ARMAMENT,
    BOX,
    UNKNOWN  // objeto invalido
};

struct Object {
    ObjectType type;
    QString iconPath;
    QSize size;
    QPointF centerPos;
    QPixmap icon;

    explicit Object(ObjectType type): type(type) {
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
        } // tengo que ver lo de UNKNOWN

        QPixmap i(iconPath);
        icon = i.scaled(size.width() * PIXEL_SIZE, size.height() * PIXEL_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    // este constructor lo agrego para que QT tome a la clase Object como un item de QT.
    Object() : type(UNKNOWN), size(0, 0), centerPos(0, 0) {
        icon = QPixmap();
    }

    // setea la posicion central del objeto.
    // el parametro booleano determina si la posicion recibida es la central o la de la esquina superior izquierda
    // si se recibe la de la esquina, se realizan los calculos para obtener la central y setearla correctamente.
    void setCenterPosition(QPointF pos, bool isTopLeftPos) {
        if (isTopLeftPos)
            centerPos = QPointF(pos.x() + size.width()/2, pos.y() + size.height()/2);
        else
            centerPos = pos;
    }

    QPointF getBoundingPos() const {
        return QPointF{(centerPos.x()) - size.width() / 2, centerPos.y() - size.height() / 2};
    }
};

Q_DECLARE_METATYPE(Object)
Q_DECLARE_METATYPE(Object*)
