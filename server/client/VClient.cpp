#include "VClient.h"

VirtualClient::VirtualClient(ActiveSocket socket, GameMapMonitor& monitor):
        skt(std::move(socket)),
        sendQueue(std::make_shared<BlockingQueue<std::shared_ptr<ServerMessage>>>()),
        receiver(skt, sendQueue, monitor),
        sender(skt, sendQueue)

{
    receiver.start();
    sender.start();
}

bool VirtualClient::isConnected() { return receiver.is_alive() && sender.is_alive(); }

VirtualClient::~VirtualClient() {
    receiver.stop();
    sender.stop();
    skt.shutdown(Socket::ShutdownOptions::READ_WRITE);
    skt.close();
    // Despues ver si poner referenia nula y catch el error en el recevier.
    sendQueue->close();
    receiver.join();
    sender.join();
}
