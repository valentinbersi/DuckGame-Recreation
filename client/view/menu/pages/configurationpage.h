#pragma once

#include <QButtonGroup>

#include "Communicator.h"
#include "GameInfo.h"
#include "ui_configurationPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class configurationPage;
}
QT_END_NAMESPACE

class configurationPage: public QWidget {
    Q_OBJECT

private:
    Ui::configurationPage* ui;
    QButtonGroup* CantidadPlayersGroup;
    GameInfo& gameInfo;
    Communicator& communicator;

    /**
    * Handler que atrapa el evento push del boton joinGame
    * Se encarga de hacer la request al servidor de unirse a la partida
    * Muestra los mensajes de errores que pueden llegar del server
    * Si se conecta a la partida, emite la señal playMatchClicked()
    */
    void handlerJoinGame();

    /**
    * Handler que atrapa el evento push del boton newGame
    * Se encarga de hacer la request al servidor de crear una partida
    * Muestra los mensajes de errores que pueden llegar del server
    * Si se conecta a la partida, emite la señal playMatchClicked()
    */
    void handlerNewGame();

    /**
     * Metodo utilizado por los handlers para enviar la request al servidor.
     * Envia la solicitud (de crear o unirse) y espera una respuesta del servidor.
     * Actualiza el gameInfo con la informacion recibida desde el servidor.
     * @param request tipo de request que se recibe
     * @return true si se conecto bien, false si no lo hizo
     * Muestra el mensaje de error que puede llegar desde el servidor.
     */
    bool initMatchRequest(LobbyRequest& request);

public:
    configurationPage(QWidget* parent, GameInfo& gameInfo, Communicator& communicator);

    /**
    * Devuelve la cantidad de jugadores seleccionados para jugar localmente (1 o 2)
    */
    int getSelectedPlayers() const;
    ~configurationPage() override;

signals:
    void playMatchClicked();
    void backClicked();
};
