#ifndef DUCKGAME_LOBBYQT_H
#define DUCKGAME_LOBBYQT_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"

class LobbyQT : public QObject{
    Q_OBJECT

private:
QApplication app;
MainWindow mainWindow;

public:
    explicit LobbyQT(int argc, char* argv[]);
    int exec();

signals:
    void initMatch();

};
#endif  // DUCKGAME_LOBBYQT_H
