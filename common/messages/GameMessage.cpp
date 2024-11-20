
#include "GameMessage.h"

GameMessage::GameMessage(InputAction action, u8 player):
        ClientMessage(MessageType::Game), action(action), player(player) {}

void GameMessage::send(ClientSendProtocol& clientProtocol) {
    clientProtocol.sendGameMessage(type, action, player);
}


bool GameMessage::operator==(const GameMessage& other) const {
    return type == other.type && action == other.action && player == other.player;
}
GameMessage::~GameMessage() = default;
