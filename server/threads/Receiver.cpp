
#include "Receiver.h"
#include "MovementCommand.h"

Receiver::Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queue_ptr,
                   std::shared_ptr<BlockingQueue<std::shared_ptr<Message>>> queueSender,
                   GameMapMonitor& monitor):
        recvProtocol(socket),
        gameQueue(queue_ptr),
        lobbyResolver(monitor, queueSender, queue_ptr) {}

void Receiver::run() {
    try {
        while (_keep_running) {
        
            std::unique_ptr<Message> message = recvProtocol.receiveMessage();
            if (message->type == MessageType::Game){
                const GameMessage* gameMessage = dynamic_cast<const GameMessage*>(message.get());
                gameQueue->push(std::make_unique<MovementCommand>(0, gameMessage->action));
            }else{
                const LobbyMessage* lobbyMessage = dynamic_cast<const LobbyMessage*>(message.get());
                lobbyResolver.resolveRequest(*lobbyMessage);
            }
        }

        // }catch(){

    } catch (...) {}
}

void Receiver::stop(){
    _keep_running = false;
    _is_alive = false;
}

Receiver::~Receiver() = default;
