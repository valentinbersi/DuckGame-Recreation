#include <QApplication>

#include "Object.h"
#include "ViewController.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    qRegisterMetaType<Object>("Object");
    qRegisterMetaType<Object*>("Object*");
    qRegisterMetaType<Object*>("Object&");
    qRegisterMetaType<const Object*>("const Object*");
    ViewController w;
    w.show();
    return a.exec();
}
