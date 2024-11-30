#ifndef DUCKGAME_WAITINGPAGE_H
#define DUCKGAME_WAITINGPAGE_H

#include <QWidget>

#include "Communicator.h"
#include "DuckData.h"
#include "GameInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WaitingPage;
}
QT_END_NAMESPACE

class WaitingPage: public QWidget {
    Q_OBJECT

private:
    Ui::WaitingPage* ui;
    Communicator& communicator;
    GameInfo& gameInfo;
    QTimer* timer;

    //    std::unordered_map<DuckData::Id, QPixmap> mapDuckIcons =
    //            {{DuckData::Id::White, QPixmap(":/ducks/whiteDuck")},
    //             {DuckData::Id::Grey, QPixmap(":/ducks/greyDuck")},
    //             {DuckData::Id::Orange, QPixmap(":/ducks/orangeDuck")},
    //             {DuckData::Id::Yellow, QPixmap(":/ducks/yellowDuck")}};

    void requestStartGame();
    void recvServerMessage();
    static QString getDuckIconPath(DuckData::Id id);

public:
    WaitingPage(QWidget* parent, Communicator& communicator, GameInfo& gameInfo);
    ~WaitingPage() override;

signals:
    void startMatch();
};


#endif  // DUCKGAME_WAITINGPAGE_H
