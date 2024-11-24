#ifndef DUCKGAME_WAITINGPAGE_H
#define DUCKGAME_WAITINGPAGE_H

#include <QWidget>

#include "Communicator.h"
#include "GameInfo.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class WaitingPage;
}
QT_END_NAMESPACE

class WaitingPage: public QWidget {
    Q_OBJECT

private:
    // cppcheck-suppress unusedStructMember
    Ui::WaitingPage* ui;
    // cppcheck-suppress unusedStructMember
    bool isHost;
    Communicator& communicator;
    GameInfo& gameInfo;
    // cppcheck-suppress unusedStructMember
    QTimer* timer;

    void requestStartGame();
    void recvServerMessage();

public:
    WaitingPage(QWidget* parent, bool isHost, Communicator& communicator, GameInfo& gameInfo);
    ~WaitingPage() override;

signals:
    void startMatch();
};


#endif  // DUCKGAME_WAITINGPAGE_H
