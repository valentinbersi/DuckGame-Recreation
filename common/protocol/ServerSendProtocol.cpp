
#include "ServerSendProtocol.h"

#include <cstring>

#include "Math.h"
#include "ServerMessage.h"


ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ServerSendProtocol::sendGameObject2DData(const GameObject2DData* obj2Data) {
    // NOTA:DESPUES TALVEZ DEBA MANDAR EL PROPIO ID, POR AHORA NO
    sendInt(Math::floatToInteger(obj2Data->position.x()));
    sendInt(Math::floatToInteger(obj2Data->position.y()));
    sendInt(Math::floatToInteger(obj2Data->rotation));
}
void ServerSendProtocol::sendDuckData(const DuckData* duckData) {
    sendByte(static_cast<unsigned char>(duckData->duckID));
    sendByte(duckData->life);
    sendByte(static_cast<unsigned char>(duckData->gun->gunID));
    sendShort(static_cast<u16>(duckData->extraData.to_ulong()));
}

void ServerSendProtocol::sendDuck(const GameObjectData& objData) {
    sendByte(static_cast<unsigned char>(objData.objectID));
    sendGameObject2DData(dynamic_cast<const GameObject2DData*>(&objData));
    sendDuckData(dynamic_cast<const DuckData*>(&objData));
}

void ServerSendProtocol::sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers) {
    sendShort(matchID);
    sendByte(startGame);
    sendByte(connectedPlayers);
}

void ServerSendProtocol::sendLen(u16 len) { sendShort(len); }

void ServerSendProtocol::sendMessage(std::shared_ptr<ServerMessage>&& message) {
    sendByte(message->type);
    message->send(*this);
}
