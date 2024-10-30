
#include "Receiver.h"

Receiver::Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queue_ptr,
                   std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> queueSender,
                   GameMapMonitor& monitor):
        recvProtocol(socket),
        gameQueue(queue_ptr),
        lobbyResolver(monitor, queueSender, queue_ptr) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            // se viene refactor
            Message message = recvProtocol.receiveMessage();
            // std::unique_ptr<Command> = factory.makeCommand(message);
            // gamequeue.push()
        }

        // }catch(){

    } catch (...) {}
}