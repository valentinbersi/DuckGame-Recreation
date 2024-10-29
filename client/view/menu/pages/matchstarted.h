//
// Created by tomas-hevia on 25/10/24.
//

#ifndef DUCKGAME_MATCHSTARTED_H
#define DUCKGAME_MATCHSTARTED_H

#include "ui_matchStarted.h"

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class matchStarted;
}
QT_END_NAMESPACE

class matchStarted: public QWidget {
    Q_OBJECT

public:
    explicit matchStarted(QWidget* parent = nullptr);
    ~matchStarted() override;

private:
    Ui::matchStarted* ui;
};


#endif  // DUCKGAME_MATCHSTARTED_H
