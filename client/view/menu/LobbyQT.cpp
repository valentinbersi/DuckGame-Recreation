#include "LobbyQT.h"

#include "mainwindow.h"

LobbyQT::LobbyQT(int argc, char* argv[], Communicator& communicator):
        app(argc, argv),
        communicator(communicator),
        mainWindow(nullptr, communicator) {
    mainWindow.show();

    connect(&mainWindow, &MainWindow::startGame, this, &LobbyQT::initMatch);
    connect(this, &LobbyQT::initMatch, &app, &QApplication::quit);
}

int LobbyQT::exec() { return app.exec(); }