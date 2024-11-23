
#include "Receiver.h"

#include <syslog.h>

#include "ExitCommand.h"
#include "LibError.h"
#include "MovementCommand.h"

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
            gameQueue->push(
                    factory.createCommand(gameMessage.action, clientID - 1 + gameMessage.player));
        }

    } catch (const ClosedQueue& err) {
        // expected
    } catch (const LibError& err) {
        if (gameQueue != nullptr) {
            gameQueue->push(std::make_unique<ExitCommand>(clientID));
            gameQueue->push(std::make_unique<ExitCommand>(clientID + 1));
        }
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _keep_running = false;
}

void Receiver::stop() {
    _keep_running = false;
    _is_alive = false;
}

Receiver::~Receiver() = default;
