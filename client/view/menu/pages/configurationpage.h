#ifndef DUCKGAME_CONFIGURATIONPAGE_H
#define DUCKGAME_CONFIGURATIONPAGE_H

#include <QButtonGroup>
#include <QWidget>

#include "ui_configurationPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class configurationPage;
}
QT_END_NAMESPACE

class configurationPage: public QWidget {
    Q_OBJECT

public:
    explicit configurationPage(QWidget* parent = nullptr);
    int getSelectedPlayers() const;
    ~configurationPage() override;

signals:
    void newGameClicked();
    void joinGameClicked();
    void backClicked();

private:
    Ui::configurationPage* ui;
    QButtonGroup* CantidadPlayersGroup;
};

#endif  // DUCKGAME_CONFIGURATIONPAGE_H
