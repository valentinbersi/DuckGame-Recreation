
#include "GameMessage.h"

GameMessage::GameMessage(InputAction action): ClientMessage(MessageType::Game), action(action) {}
   
void GameMessage::send(ClientSendProtocol& clientProtocol){
    clientProtocol.sendGameMessage(type, action);
}

GameMessage::~GameMessage() = default;