
#include "ClientSendProtocol.h"

ClientSendProtocol::ClientSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ClientSendProtocol::sendMessage(const ClientMessage& message) {
    sendByte(message.type);
    sendByte(message.action);
}
