
#include "ServerSendProtocol.h"

#include <cstring>

#include "Math.h"
#include "ServerMessage.h"


ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ServerSendProtocol::sendVector2(const Vector2& vector) {
    sendInt(Math::floatToInteger(vector.x()));
    sendInt(Math::floatToInteger(vector.y()));
}

void ServerSendProtocol::sendRectangle(const Rectangle& rectangle) {
    sendVector2(rectangle.position());
    sendVector2(rectangle.size());
}

void ServerSendProtocol::sendDuckData(const DuckData& duckData) {
    sendByte(static_cast<unsigned char>(duckData.duckID));
    sendByte(duckData.life);
    sendByte(static_cast<unsigned char>(duckData.gunID));
    sendShort(static_cast<u16>(duckData.extraData.to_ulong()));
    sendVector2(duckData.rectangle.center());
}

void ServerSendProtocol::sendBlock(const SizedObjectData& objData) {
    sendRectangle(objData.rectangle);
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
