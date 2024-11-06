
#include "Sender.h"

Sender::Sender(ActiveSocket& socket,
               std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& queue):
        sendProtocol(socket), sendQueue(queue) {}

void Sender::run() {
    try {
        while (_keep_running) {
            sendProtocol.sendMessage(sendQueue->pop());
        }

        // }catch(){

    } catch (...) {}
}

void Sender::stop() {
    _keep_running = false;
    _is_alive = false;
}

Sender::~Sender() = default;
