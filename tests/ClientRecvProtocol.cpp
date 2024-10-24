
#include "ClientRecvProtocol.h"
#include "DuckData.h"

ClientRecvProtocol::ClientRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvPlayerData(){
    float posX = recvInt();
    float posY = recvInt();
    float rotation = recvInt();
    u8 duckID = recv_byte();
    u8 life = recv_byte();
    u8 gunID = recv_byte(); 
    u8 actions = recv_byte();
    return std::make_unique<DuckData>(Vector2(posX,posY), rotation, static_cast<DuckID>(duckID), life,
                                        std::make_unique<EquippedGunData>(static_cast<GunID>(gunID)), 
                                        actions);
}

std::unique_ptr<GameObjectData> ClientRecvProtocol::recvData(){
    //por ahora solo puede ser objeto tipo DuckData, despues iria algun diccionario
    recv_byte();
    recv_byte();
    //Pueden ser headers utiles para identificar el tipo de obj y obj 2d, no hacen falta en la contrusccion

    return recvPlayerData(); //por ahora simplemente devolvemos el unico tipo que tenemos.
}

GameStatus ClientRecvProtocol::receiveMessage(){
    u16 size = recvShort();
    GameStatus status;
    while(size){
        std::unique_ptr<GameObjectData> objData = std::move(recvData());
        status.addObject(std::move(objData));
        size--;
    }
    return status;
}
