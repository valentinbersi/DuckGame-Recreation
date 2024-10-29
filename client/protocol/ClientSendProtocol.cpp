#include "ClientSendProtocol.h"

ClientSendProtocol::ClientSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ClientSendProtocol::sendMessage(const ClientMessage& message) {
    if(message.type == MessageType::Game){
        const GameMessage* msg = dynamic_cast<const GameMessage*>(&message);
        sendByte(msg->action);
    } else {
        const LobbyMessage* msg = dynamic_cast<const LobbyMessage*>(&message);
        sendByte(msg->request);
    }
    
}
