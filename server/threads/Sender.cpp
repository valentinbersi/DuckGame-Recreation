
#include "Sender.h"
#include <syslog.h>
#include "LibError.h"
#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."
#define FORMAT "%s"

Sender::Sender(ActiveSocket& socket,
               std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& queue):
        sendProtocol(socket), sendQueue(queue) {}

void Sender::run() noexcept {
    try {
        while (_keep_running) {
            sendProtocol.sendMessage(sendQueue->pop());
        }

    } catch (const ClosedQueue& err) {
        //expected 
    } catch (const LibError& err) {
        //expected
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _keep_running = false;
}

void Sender::stop() {
    sendQueue->close();
    _keep_running = false;
    _is_alive = false;
}

Sender::~Sender() {};
