#include "VClient.h"

VirtualClient::VirtualClient(ActiveSocket socket, GameMapMonitor& monitor, u16 clientID):
        skt(std::move(socket)),
        id(clientID),
        sendQueue(std::make_shared<BlockingQueue<std::shared_ptr<ServerMessage>>>()),
        receiver(skt, sendQueue, monitor, id),
        sender(skt, sendQueue)

{
    receiver.start();
    sender.start();
}

bool VirtualClient::isConnected() { return receiver.is_alive() && sender.is_alive(); }

VirtualClient::~VirtualClient() {
    receiver.stop();
    sender.stop();
    try{
        skt.shutdown(Socket::ShutdownOptions::READ_WRITE);
        skt.close();
    }catch(const LibError& err){
        //client already shutdown and closed socket
    }
    receiver.join();
    sender.join();
}
