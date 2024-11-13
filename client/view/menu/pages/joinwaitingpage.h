#ifndef DUCKGAME_JOINWAITINGPAGE_H
#define DUCKGAME_JOINWAITINGPAGE_H

#include <QWidget>

#include "Communicator.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class joinWaitingPage;
}
QT_END_NAMESPACE

class joinWaitingPage: public QWidget {
    Q_OBJECT

private:
    Ui::joinWaitingPage* ui;
    Communicator& communicator;
    QTimer* timer;

public:
    joinWaitingPage(QWidget* parent, Communicator& communicator);
    void recvServerMessage();
    ~joinWaitingPage() override;

signals:
    void matchStarted();
};


#endif  // DUCKGAME_JOINWAITINGPAGE_H
