//
// Created by tomas-hevia on 1/11/24.
//

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

public:
    explicit joinWaitingPage(QWidget* parent = nullptr);
    ~joinWaitingPage() override;

private:
    Ui::joinWaitingPage* ui;
};


#endif  // DUCKGAME_JOINWAITINGPAGE_H
