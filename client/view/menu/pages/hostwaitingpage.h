//
// Created by tomas-hevia on 1/11/24.
//

#ifndef DUCKGAME_HOSTWAITINGPAGE_H
#define DUCKGAME_HOSTWAITINGPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class hostWaitingPage;
}
QT_END_NAMESPACE

class hostWaitingPage: public QWidget {
    Q_OBJECT

public:
    explicit hostWaitingPage(QWidget* parent = nullptr);
    ~hostWaitingPage() override;

private:
    Ui::hostWaitingPage* ui;
};


#endif  // DUCKGAME_HOSTWAITINGPAGE_H
