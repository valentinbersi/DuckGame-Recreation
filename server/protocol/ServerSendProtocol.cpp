
#include "ServerSendProtocol.h"

ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ServerSendProtocol::sendMessage(std::shared_ptr<GameStatus>& message) {
    // A implementar
}
