#include <QApplication>
#include <iostream>

#include "Object.h"
#include "Resource.h"
#include "ViewController.h"

int main(int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "hr:")) != -1) {
        switch (opt) {
            case 'h':
                std::cout << "Usage: " << argv[0] << " [-h] [-r resources_directory]" << std::endl;
                return 0;
            case 'r': {
                std::string resourcesPath(optarg);
                if (resourcesPath.back() != '/')
                    resourcesPath += '/';
                Resource::get().setSearchPath(std::move(resourcesPath));

            } break;
            default:
                std::cerr << "Usage: " << argv[0] << " [-h] [-r resources_directory]" << std::endl;
                return -1;
        }
    }

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
