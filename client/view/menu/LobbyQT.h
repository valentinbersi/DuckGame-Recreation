#ifndef DUCKGAME_LOBBYQT_H
#define DUCKGAME_LOBBYQT_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>

#include "Communicator.h"
#include "mainwindow.h"

class LobbyQT: public QObject {
    Q_OBJECT

private:
    QApplication app;
    MainWindow mainWindow;
    Communicator& communicator;

public:
    LobbyQT(int argc, char* argv[], Communicator& communicator);
    int exec();

signals:
    void initMatch();
};
#endif  // DUCKGAME_LOBBYQT_H