
#include "Receiver.h"

#include "MovementCommand.h"
#include "LibError.h"
#include <syslog.h>

#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."
#define FORMAT "%s"

Receiver::Receiver(ActiveSocket& socket,
                   std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> queueSender,
                   GameMapMonitor& monitor, const u16& clientID):
        recvProtocol(socket),
        gameQueue(nullptr),
        clientID(clientID),
        lobbyResolver(monitor, queueSender, clientID) {}

void Receiver::run() noexcept {
    try {
        while (gameQueue == nullptr) {
            LobbyMessage lobbyMessage = recvProtocol.receiveLobbyMessage();
            gameQueue = lobbyResolver.resolveRequest(lobbyMessage);
        }

        while (_keep_running) {
            GameMessage gameMessage = recvProtocol.receiveGameMessage();
            gameQueue->push(std::make_unique<MovementCommand>(clientID-1+gameMessage.player, gameMessage.action));
        }

    } catch (const LibError& err) {
        if (is_alive()){
            syslog(LOG_CRIT, FORMAT, err.what());
        }
        //expected otherwise
    } catch (const ClosedQueue& err) {
        //expected
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _keep_running = false;
    _is_alive = false;   
}

void Receiver::stop() {
    _keep_running = false;
    _is_alive = false;
}

Receiver::~Receiver() {};
