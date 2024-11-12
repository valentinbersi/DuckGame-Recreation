#ifndef DUCKGAME_HOSTWAITINGPAGE_H
#define DUCKGAME_HOSTWAITINGPAGE_H

#include <QWidget>

#include "Communicator.h"
#include "GameInfo.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class hostWaitingPage;
}
QT_END_NAMESPACE

class hostWaitingPage: public QWidget {
    Q_OBJECT

private:
    Ui::hostWaitingPage* ui;
    Communicator& communicator;
    GameInfo& gameInfo;
    QTimer* timer;

    void requestStartGame();
    void recvServerMessage();

public:
    hostWaitingPage(QWidget* parent, Communicator& communicator, GameInfo& gameInfo);
    ~hostWaitingPage() override;

signals:
    void startMatch();
};


#endif  // DUCKGAME_HOSTWAITINGPAGE_H
