#ifndef DUCKGAME_MATCHSETUP_H
#define DUCKGAME_MATCHSETUP_H

#include <QWidget>

#include "Communicator.h"
#include "GameInfo.h"
#include "LobbyMessage.h"
#include "ui_matchSetup.h"

enum MatchMode { newMatch, joinMatch };

QT_BEGIN_NAMESPACE
namespace Ui {
class matchSetup;
}
QT_END_NAMESPACE

class matchSetup: public QWidget {
    Q_OBJECT

private:
    Ui::matchSetup* ui;
    MatchMode matchMode;
    Communicator& communicator;
    GameInfo& gameInfo;

    bool validateData();
    void onPlayClicked();
    bool initMatchRequest();

public:
    matchSetup(QWidget* parent, MatchMode matchMode, Communicator& communicator,
               GameInfo& gameInfo);
    ~matchSetup() override;

signals:
    void playMatchClicked();
    void backClicked();
};


#endif  // DUCKGAME_MATCHSETUP_H
