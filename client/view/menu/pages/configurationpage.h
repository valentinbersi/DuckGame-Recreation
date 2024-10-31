#ifndef DUCKGAME_CONFIGURATIONPAGE_H
#define DUCKGAME_CONFIGURATIONPAGE_H

#include <QButtonGroup>
#include <QWidget>

#include "GameInfo.h"
#include "MyLobbyMessage.h"
#include "ui_configurationPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class configurationPage;
}
QT_END_NAMESPACE

class configurationPage: public QWidget {
    Q_OBJECT

private:
    Ui::configurationPage* ui;
    QButtonGroup* CantidadPlayersGroup;
    LobbyMessage_& message;
    void handleJoinGame();
    void handleNewGame();

public:
    configurationPage(QWidget* parent, LobbyMessage_& message);
    int getSelectedPlayers() const;
    ~configurationPage() override;

signals:
    void newGameClicked();
    void joinGameClicked();
    void backClicked();
};

#endif  // DUCKGAME_CONFIGURATIONPAGE_H
