#include "ComSender.h"

#define ERROR_MSG "UNOWN ERROR DURING RUNTIME."

CommunicatorSender::CommunicatorSender(ActiveSocket& socket, BlockingQueue<Message>& queue) : 
                                        sendProtocol(socket),
                                        sendQueue(queue) {}

void CommunicatorSender::run(){
    try{
        while(_keep_running){
            sendProtocol.sendMessage(sendQueue.pop());
        }

    }catch(const ClosedQueue& error){
        /**
         * De entrar aqui significa que la queue por fuera fue cerrada,
         * es una excepcion esperada.
         */
    }catch(const LibError& error){
        /**
         * De entrar aqui se asume que el error es o bien por cierre del
         * socket por parte del comunicador, que seria esperado, o 
         * de provocado por el servidor. De ambas formas se sale ordenadamente
         */
    }catch(...){
        syslog(LOG_CRIT, ERROR_MSG);
    }
    _is_alive = false;
    _keep_running= false;
}

void CommunicatorSender::stop(){
    _is_alive = false;
    _keep_running = false;
}

CommunicatorSender::~CommunicatorSender() = default;
