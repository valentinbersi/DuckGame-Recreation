#include <QApplication>

#include "Object.h"
#include "ViewController.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    /** registro la clase Object como tipo de Qt*/
    qRegisterMetaType<Object>("Object");
    qRegisterMetaType<Object*>("Object*");
    qRegisterMetaType<Object*>("Object&");
    qRegisterMetaType<const Object*>("const Object*");

    ViewController w;
    w.show();
    return QApplication::exec();
}
