#pragma once

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <utility>

struct Object {
    QString name;
    int heigth;
    int width;
    QString icon;

    Object(QString name, int heigth, int width, QString icon)
            : name(std::move(name)),
            heigth(heigth),
            width(width),
            icon(std::move(icon)) {}
};
