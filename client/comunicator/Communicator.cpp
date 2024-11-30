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

int Communicator::percentOfMessagesToReceive(int amount) {
    int step = 4;
    return amount / step + 1;
}

std::optional<GameStatus> Communicator::tryRecvLast() {
    return recvQueueGame.tryPopPercent([this](int amount) 
    { return percentOfMessagesToReceive(amount); });
}

std::optional<ReplyMessage> Communicator::tryRecvReply() { return recvQueueLobby.try_pop(); }

ReplyMessage Communicator::blockingRecv() { return recvQueueLobby.pop(); }

Communicator::~Communicator() {
    sender.stop();
    receiver.stop();
    skt.shutdown(Socket::ShutdownOptions::READ_WRITE);
    skt.close();
    sendQueue.close();
    recvQueueGame.close();
    sender.join();
    receiver.join();
}
