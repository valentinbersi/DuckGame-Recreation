
#include "Receiver.h"
#include "MovementCommand.h"

Receiver::Receiver(ActiveSocket& socket, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> queueSender,
                   GameMapMonitor& monitor):
        recvProtocol(socket),
        gameQueue(nullptr),
        lobbyResolver(monitor, queueSender) {}

void Receiver::run() {
    try {
        while (gameQueue == nullptr) {
            std::unique_ptr<ClientMessage> message = recvProtocol.receiveMessage();
            const LobbyMessage* lobbyMessage = dynamic_cast<const LobbyMessage*>(message.get());
            gameQueue = lobbyResolver.resolveRequest(*lobbyMessage);
        }

        while (_keep_running){
            std::unique_ptr<ClientMessage> message = recvProtocol.receiveMessage();
            const GameMessage* gameMessage = dynamic_cast<const GameMessage*>(message.get());
            gameQueue->push(std::make_unique<MovementCommand>(0, gameMessage->action));
        }

        // }catch(){
    } catch (...) {}
}

void Receiver::stop(){
    _keep_running = false;
    _is_alive = false;
}

Receiver::~Receiver() = default;
