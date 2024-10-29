#include "LobbyQT.h"
#include "mainwindow.h"

LobbyQT::LobbyQT(int argc, char** argv)
    : app(argc, argv) {
    mainWindow.show();

    connect(&mainWindow, &MainWindow::initMatch, this, &LobbyQT::initMatch);
    connect(this, &LobbyQT::initMatch, &app, &QApplication::quit);
}

int LobbyQT::exec() {
    return app.exec();
}
