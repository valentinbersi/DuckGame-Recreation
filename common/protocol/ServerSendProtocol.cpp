
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

void ServerSendProtocol::sendRoundData(bool roundEnded, bool setEnded, bool gameEnded) {
    sendByte(roundEnded);
    sendByte(setEnded);
    sendByte(gameEnded);
}

void ServerSendProtocol::sendDuckData(const DuckData& duckData) {
    sendByte(static_cast<u8>(duckData.duckID));
    sendByte(static_cast<u8>(duckData.direction));
    sendByte(static_cast<u8>(duckData.gunID));
    sendShort(static_cast<u16>(duckData.extraData.to_ulong()));
    sendInt(duckData.roundsWon);
    sendVector2(duckData.rectangle.center());
}

void ServerSendProtocol::sendItemData(const ItemData& objData) {
    sendByte(static_cast<unsigned char>(objData.id));
    sendRectangle(objData.rectangle);
}

void ServerSendProtocol::sendBlock(const SizedObjectData& objData) {
    sendRectangle(objData.rectangle);
}

void ServerSendProtocol::sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers,
                                          DuckData::Id color1, DuckData::Id color2,
                                          const std::string& error) {
    sendShort(matchID);
    sendByte(startGame);
    sendByte(connectedPlayers);
    sendByte(static_cast<u8>(color1));
    sendByte(static_cast<u8>(color2));
    sendString(error);
}

void ServerSendProtocol::sendLen(u16 len) { sendShort(len); }

void ServerSendProtocol::sendMessage(std::shared_ptr<ServerMessage>&& message) {
    sendByte(message->type);
    message->send(*this);
}
