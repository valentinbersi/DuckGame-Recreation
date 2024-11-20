
#include "ClientSendProtocol.h"

#include <memory>
#include <string>

#include "ClientMessage.h"

ClientSendProtocol::ClientSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ClientSendProtocol::sendLobbyMessage(u8 type, u8 request, u8 playerCount,
                                          const std::string& player1Name,
                                          const std::string& player2Name, u16 matchId) {
    sendByte(type);
    sendByte(request);
    sendByte(playerCount);
    sendString(player1Name);
    sendString(player2Name);
    sendShort(matchId);
}

void ClientSendProtocol::sendGameMessage(u8 type, u8 action, u8 player) {
    sendByte(type);
    sendByte(action);
    sendByte(player);
}

void ClientSendProtocol::sendMessage(std::unique_ptr<ClientMessage> message) {
    message->send(*this);
}
