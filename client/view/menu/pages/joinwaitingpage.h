#ifndef DUCKGAME_JOINWAITINGPAGE_H
#define DUCKGAME_JOINWAITINGPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class joinWaitingPage;
}
QT_END_NAMESPACE

class joinWaitingPage: public QWidget {
    Q_OBJECT

private:
    Ui::joinWaitingPage* ui;

public:
    explicit joinWaitingPage(QWidget* parent = nullptr);
    ~joinWaitingPage() override;

signals:
    void matchStarted();
};


#endif  // DUCKGAME_JOINWAITINGPAGE_H
