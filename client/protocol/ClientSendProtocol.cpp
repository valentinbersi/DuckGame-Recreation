
#include "ClientSendProtocol.h"

ClientSendProtocol::ClientSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ClientSendProtocol::sendMessage(std::unique_ptr<Message> message) {
    sendByte(message->type);
    if (message->type == MessageType::Game) {
        const GameMessage* msg = dynamic_cast<const GameMessage*>(&*message);
        sendByte(msg->action);
    } else {
        const LobbyMessage* msg = dynamic_cast<const LobbyMessage*>(&*message);
        sendByte(msg->request);
        sendString(msg->usrName);
        sendShort(msg->matchId);
    }
}
