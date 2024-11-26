#pragma once

#include <QButtonGroup>
#include <QWidget>

#include "Communicator.h"
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
    Communicator& communicator;

    void handlerJoinGame();  // ¿?
    void handlerNewGame();   // ¿?

    bool initMatchRequest(LobbyRequest& request);

public:
    configurationPage(QWidget* parent, GameInfo& gameInfo, Communicator& communicator);
    int getSelectedPlayers() const;
    ~configurationPage() override;

signals:
    void playMatchClicked();
    void backClicked();
};
