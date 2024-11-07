
#include "GameMessage.h"

GameMessage::GameMessage(InputAction action, u8 player): ClientMessage(MessageType::Game), action(action), player(player) {}

void GameMessage::send(ClientSendProtocol& clientProtocol) {
    clientProtocol.sendGameMessage(type, action, player);
}

GameMessage::~GameMessage() = default;