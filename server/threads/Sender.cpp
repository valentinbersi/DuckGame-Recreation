
#include "Sender.h"
#include <syslog.h>
#include "LibError.h"
#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."

Sender::Sender(ActiveSocket& socket,
               std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& queue):
        sendProtocol(socket), sendQueue(queue) {}

void Sender::run() noexcept {
    try {
        while (_keep_running) {
            sendProtocol.sendMessage(sendQueue->pop());
        }

    } catch (const ClosedQueue& err) {
        if (is_alive()){
            syslog(LOG_INFO, err.what());
        }
        //expected otherwise
    } catch (const LibError& err) {
        if (is_alive()){
            syslog(LOG_CRIT, err.what());
        }
        //expected otherwise
    } catch (...) {
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _keep_running = false;
    _is_alive = false;   
}

void Sender::stop() {
    sendQueue->close();
    _keep_running = false;
    _is_alive = false;
}

Sender::~Sender() {};
