#include "LobbyQT.h"

#include "mainwindow.h"

LobbyQT::LobbyQT(int argc, char** argv /*, ActiveSocket& socket*/):
        app(argc, argv), mainWindow(nullptr) {
    mainWindow.show();

    connect(&mainWindow, &MainWindow::initMatch, this, &LobbyQT::initMatch);
    connect(this, &LobbyQT::initMatch, &app, &QApplication::quit);
}

int LobbyQT::exec() { return app.exec(); }
