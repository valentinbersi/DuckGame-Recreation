#include "ComReceiver.h"

#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."

CommunicatorReceiver::CommunicatorReceiver(ActiveSocket& socket,
                                           BlockingQueue<ReplyMessage>& queueLobby,
                                           BlockingQueue<GameStatus>& queueGame):
        recvProtocol(socket), recvQueueLobby(queueLobby) ,recvQueueGame(queueGame) {}

void CommunicatorReceiver::run() {
    try {
        u8 startGame;
        do{
            ReplyMessage reply = recvProtocol.recvReplyMessage();
            startGame = reply.startGame;
            recvQueueLobby.push(std::move(reply));
        } while (!startGame && _keep_running);

        while(_keep_running){
            recvQueueGame.push(std::move(recvProtocol.recvGameStatus()));
        }

    } catch (const ClosedQueue& error) {
        //chequear cual fue
    } catch (const LibError& error) {
        /**
         * De entrar aqui se asume que el error es o bien por cierre del
         * socket por parte del comunicador, que seria esperado, o
         * de provocado por el servidor. De ambas formas se sale ordenadamente
         */
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _is_alive = false;
    _keep_running = false;
}

void CommunicatorReceiver::stop() {
    _is_alive = false;
    _keep_running = false;
}

CommunicatorReceiver::~CommunicatorReceiver() = default;