#pragma once

#include "ActiveSocket.h"
#include "Communicator.h"
#include "QApplication"
#include "gameMenu.h"

class GameLauncher: public QObject {
    Q_OBJECT

private:
    Communicator communicator;
    QApplication app;
    bool twoPlayersLocal;
    GameMenu menu;
    bool startGame;

public:
    GameLauncher(int argc, char* argv[], cppstring hostname, cppstring servname);
    void exec();

private slots:
    void startedSDL();
};
