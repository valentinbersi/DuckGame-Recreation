#include "Communicator.h"

Communicator::Communicator(const std::string& hostname, const std::string& servername):
        skt(hostname.c_str(), servername.c_str()),
        sendQueue(),
        recvQueue(),
        sender(skt, sendQueue),
        receiver(skt, recvQueue) {
    sender.start();
    receiver.start();
}

bool Communicator::trysend(std::unique_ptr<Message> message) { return sendQueue.try_push(std::move(message)); }

std::optional<std::unique_ptr<Message>> Communicator::tryrecv() { return recvQueue.try_pop(); }

std::queue<std::unique_ptr<Message>> Communicator::recvAll(){return recvQueue.popAll();}

Communicator::~Communicator() {
    sender.stop();
    receiver.stop();
    skt.close();
    sendQueue.close();
    recvQueue.close();
    sender.join();
    receiver.join();
}
