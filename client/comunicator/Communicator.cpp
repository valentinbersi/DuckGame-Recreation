#include "Communicator.h"

#include <memory>
#include <string>
#include <utility>

Communicator::Communicator(const std::string& hostname, const std::string& servername):
        skt(hostname.c_str(), servername.c_str()),
        sendQueue(),
        recvQueueLobby(),
        recvQueueGame(),
        sender(skt, sendQueue),
        receiver(skt, recvQueueLobby, recvQueueGame) {
    sender.start();
    receiver.start();
}

bool Communicator::trysend(std::unique_ptr<ClientMessage> message) {
    return sendQueue.try_push(std::move(message));
}

std::optional<GameStatus> Communicator::tryrecv() { return recvQueueGame.try_pop(); }

std::optional<GameStatus> Communicator::tryRecvLast() {
    std::queue<GameStatus> queue = recvQueueGame.popAll();
    if (queue.empty()) {
        return std::nullopt;
    }
    GameStatus message = std::move(queue.back());
    queue.pop();
    return message;
}

std::optional<ReplyMessage> Communicator::tryRecvReply() { return recvQueueLobby.try_pop(); }

ReplyMessage Communicator::blockingRecv() { return recvQueueLobby.pop(); }

Communicator::~Communicator() {
    sender.stop();
    receiver.stop();
    skt.close();
    sendQueue.close();
    recvQueueGame.close();
    sender.join();
    receiver.join();
}
