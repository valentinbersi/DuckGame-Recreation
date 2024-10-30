#include "common_init.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDebug>


QString common_init(QWidget* widget, const QString& backgroundPath){
    QPixmap pixmap(backgroundPath);
    QSize windowSize = widget->size();
    QPixmap scaledPixmap = pixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    widget->setPalette(palette);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Jersey10-Regular.ttf");
    if (fontId == -1) {
        qWarning("No se pudo cargar la fuente personalizada.");
        return "";
    } else {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily, 25);
        QApplication::setFont(font);
        return fontFamily;
    }
}
