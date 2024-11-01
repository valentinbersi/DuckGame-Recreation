#ifndef DUCKGAME_CONFIGURATIONPAGE_H
#define DUCKGAME_CONFIGURATIONPAGE_H

#include <QButtonGroup>
#include <QWidget>

#include "GameInfo.h"
#include "LobbyMessage.h"
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
    GameInfo& gameInfo;
    void handleJoinGame();
    void handleNewGame();

public:
    configurationPage(QWidget* parent, GameInfo& gameInfo);
    int getSelectedPlayers() const;
    ~configurationPage() override;

signals:
    void newGameClicked();
    void joinGameClicked();
    void backClicked();
};

#endif  // DUCKGAME_CONFIGURATIONPAGE_H
