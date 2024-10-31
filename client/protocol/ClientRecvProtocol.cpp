#include "ClientRecvProtocol.h"
#include "LobbyMessage.h"

ClientRecvProtocol::ClientRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {
    idsMap[GameObjectID::Object2D] = [this]() -> std::unique_ptr<GameObjectData> {
        return recvDuckData();
    };
}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvDuckData() {
    float posX = Math::integerToFloat(recvInt());
    float posY = Math::integerToFloat(recvInt());
    float rotation = Math::integerToFloat(recvInt());
    u8 duckID = recv_byte();
    u8 life = recv_byte();
    u8 gunID = recv_byte();
    u16 actions = recvShort();
    return std::make_unique<DuckData>(
            Vector2(posX, posY), rotation, static_cast<DuckID>(duckID), life,
            std::make_unique<EquippedGunData>(static_cast<GunID>(gunID)), actions);
}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvData() {
    // Nota: Por ahora solo se envia desde el servidor el id de Game Object
    // Lo mas probable es que esto cambie luego, por ahora no necesito ninguno
    // de lo dos para armar las cosas.
    GameObjectID id = static_cast<GameObjectID>(recv_byte());
    return idsMap[id]();
}

std::unique_ptr<Message> ClientRecvProtocol::recvGameStatus(){
    u16 size = recvShort();
    std::unique_ptr<GameStatus> statusPtr = std::make_unique<GameStatus>();
    while (size) {
        statusPtr->gameObjects.emplace_back(recvData());
        size--;
    }
    return statusPtr;
}

std::unique_ptr<Message> ClientRecvProtocol::receiveMessage() {
    MessageType type = recv_byte();
    if (type == MessageType::Game){
        return recvGameStatus();
    }
    return std::make_unique<LobbyMessage>(LobbyRequest::JOINMATCH, "", recvShort());
}

