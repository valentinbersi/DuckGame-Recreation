
#include "ServerSendProtocol.h"
#include "DuckData.h"
#include <cstring>


ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {
    idsMap[GameObjectID::Object2D] = [this](const GameObjectData& objData){
                                            sendDuck(objData);};
}
void ServerSendProtocol::sendGameObject2DData(const GameObject2DData* obj2Data){
    
}
void ServerSendProtocol::sendDuckData(const DuckData* objData){


}

void ServerSendProtocol::sendDuck(const GameObjectData& objData){
    sendByte(static_cast<unsigned char>(objData.id));
    sendGameObject2DData(dynamic_cast<const GameObject2DData*>(&objData));
    sendDuckData(dynamic_cast<const DuckData*>(&objData));
}

void ServerSendProtocol::sendMessage(std::shared_ptr<GameStatus>& status) {
    const auto& gameObjects = status->gameObjects;
    sendShort(gameObjects.size());
    for (const auto& ptr : gameObjects){
        GameObjectID id = ptr->id;
        idsMap[id](*ptr);
    }
}
