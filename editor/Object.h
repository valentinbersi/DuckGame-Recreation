#pragma once

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <utility>

#include "ObjectConstants.h"

enum ObjectType {
    PLATFORM,
    DUCK,
    ARMAMENT,
    BOX,
    UNKNOWN  // objeto invalido
};

struct Object {
    ObjectType type;
    QString icon;
    QPointF centerPos;
    QSize size;

    explicit Object(ObjectType type): type(type) {
        switch (type) {
            case PLATFORM:
                icon = PLATFORM_ICON;
                size = QSize(PLATFORM_WIDTH, PLATFORM_HEIGHT);
                break;
            case DUCK:
                icon = DUCK_ICON;
                size = QSize(DUCK_WIDTH, DUCK_HEIGHT);
                break;
            case ARMAMENT:
                icon = ARMAMENT_ICON;
                size = QSize(ARMAMENT_WIDTH, ARMAMENT_HEIGHT);
                break;
            case BOX:
                icon = BOX_ICON;
                size = QSize(BOX_WIDTH, BOX_HEIGHT);
                break;
            default:
                qWarning() << "Tipo de objeto desconocido";
                icon = "";
                size = QSize(0, 0);
                break;
        }
    }

    void setCenterPosition(QPointF center) { centerPos = center; }

    QRectF getBoundingPos() {
        return QRectF{centerPos.x() - size.width() / 2, centerPos.y() - size.height() / 2,
                      static_cast<qreal>(size.width()), static_cast<qreal>(size.height())};
    }
};

Q_DECLARE_METATYPE(Object*)
