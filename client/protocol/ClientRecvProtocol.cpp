#include "ClientRecvProtocol.h"

ClientRecvProtocol::ClientRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {
    idsMap[GameObjectID::Object2D] = [this]() -> std::unique_ptr<GameObjectData> 
                                     { recvDuckData(); };
}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvDuckData(){
    float posX = Math::integerToFloat(recvInt());
    float posY = Math::integerToFloat(recvInt());
    float rotation = Math::integerToFloat(recvInt());
    u8 duckID = recv_byte();
    u8 life = recv_byte();
    u8 gunID = recv_byte(); 
    u16 actions = recvShort();
    return std::make_unique<DuckData>(Vector2(posX,posY), rotation, static_cast<DuckID>(duckID), life,
                                        EquippedGunData(static_cast<GunID>(gunID)), actions);
}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvData(){
    //Nota: Por ahora solo se envia desde el servidor el id de Game Object
    //Lo mas probable es que esto cambie luego, por ahora no necesito ninguno
    //de lo dos para armar las cosas.
    GameObjectID id = static_cast<GameObjectID>(recv_byte());
    return idsMap[id]();
}

GameStatus ClientRecvProtocol::receiveMessage(){
    u16 size = recvShort();
    GameStatus status;
    while(size){
        status.gameObjects.emplace_back(recvData());
        size--;
    }
    return status;
}
