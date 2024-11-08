#include "ComSync.h"

CommunicatorSync::CommunicatorSync(ActiveSocket& socket): sendProtocol(socket), recvProtocol(socket) {}

void CommunicatorSync::sendMessage(std::unique_ptr<ClientMessage> message) {
    sendProtocol.sendMessage(std::move(message));
}

ReplyMessage CommunicatorSync::recvMessage() {
    return recvProtocol.recvReplyMessage();
}

CommunicatorSync::~CommunicatorSync() {}
