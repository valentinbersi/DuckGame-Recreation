#pragma once

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <QSize>
#include <QPointF>

#include "EditorConstants.h"

enum ObjectType {
    PLATFORM,
    DUCK,
    ARMAMENT,
    BOX,
    UNKNOWN  // objeto inválido
};

struct Object {
    ObjectType type;
    QString iconPath;
    QSize size;
    QPointF centerPos;
    QPixmap icon;

    explicit Object(ObjectType type);
    Object();

    void setCenterPosition(QPointF pos, bool isTopLeftPos);
    [[nodiscard]] QPointF getBoundingPos() const;

    bool operator==(const Object& other) const;

    static std::string objectTypeToString(ObjectType type);
    static ObjectType stringToObjectType(const std::string& typeStr);
};

Q_DECLARE_METATYPE(Object)
Q_DECLARE_METATYPE(Object*)
