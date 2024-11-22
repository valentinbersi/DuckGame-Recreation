#include <QApplication>

#include "mainwindow.h"
#include "Object.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    qRegisterMetaType<Object>("Object");
    qRegisterMetaType<Object*>("Object*");
    qRegisterMetaType<Object*>("Object&");
    qRegisterMetaType<const Object*>("const Object*");
    MainWindow w;
    w.show();
    return a.exec();
}
