#include "Communicator.h"

Communicator::Communicator(const std::string& hostname, const std::string& servername):
        skt(hostname.c_str(), servername.c_str()),
        sendQueue(),
        recvQueue(),
        sync(skt),
        sender(skt, sendQueue),
        receiver(skt, recvQueue) {
    sender.start();
    receiver.start();
}

bool Communicator::trysend(std::unique_ptr<ClientMessage> message) {
    return sendQueue.try_push(std::move(message));
}

std::optional<GameStatus> Communicator::tryrecv() {
    return recvQueue.try_pop();
}

std::optional<GameStatus> Communicator::tryRecvLast() {
    std::queue<GameStatus> queue = recvQueue.popAll();
    if (queue.empty()) {
        return std::nullopt;
    }
    GameStatus message = std::move(queue.back());
    queue.pop();
    return message;
}

void Communicator::sendSync(std::unique_ptr<ClientMessage> message) { sync.sendMessage(std::move(message)); }

ReplyMessage Communicator::recvSync() { return sync.recvMessage(); }

Communicator::~Communicator() {
    sender.stop();
    receiver.stop();
    skt.close();
    sendQueue.close();
    recvQueue.close();
    sender.join();
    receiver.join();
}
