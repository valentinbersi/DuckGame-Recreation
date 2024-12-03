#pragma once

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
    u8 playersConnected;

    /**
    * Handler que captura el evento clicked del playButton
    * Envia mediante el comunicador un message al lobby para iniciar la partida
    * Antes que nada, se chequea que haya al menos 2 jugadores conectados
    */
    void requestStartGame();

    /**
     * Cada 1 segundo, cuando el timer llega al final, se handlea el timeout en este metodo.
     * Lo que hace es recibir mensajes desde el server (mediante el comunicador),
     * estos mensajes pueden ser informando la cantidad de jugadores conectados
     * o de comienzo de partida. Si es de comienzo de partida se emite startMatch().
     * Si es de jugadores conectados se actualiza el playersConnected.
     */
    void recvServerMessage();

    static QString getDuckIconPath(DuckData::Id id);

public:
    WaitingPage(QWidget* parent, Communicator& communicator, GameInfo& gameInfo);
    ~WaitingPage() override;

signals:
    void startMatch();
};