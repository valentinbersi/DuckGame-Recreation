
#include "ServerSendProtocol.h"

#include <cstring>

#include "Math.h"

#include "LobbyMessage.h"


ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {
    idsMap[GameObjectID::Object2D] = [this](const GameObjectData& objData) { sendDuck(objData); };
}

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

void ServerSendProtocol::sendMessage(std::shared_ptr<Message>&& status) {
    if (status->type == MessageType::Lobby){
        const LobbyMessage* lobbyMessage = dynamic_cast<const LobbyMessage*>(status.get());
        sendShort(lobbyMessage->matchId);
    }else{
        const GameStatus* gameStatus = dynamic_cast<const GameStatus*>(status.get());
        const auto& gameObjects = gameStatus->gameObjects;
        sendShort(gameObjects.size());
        for (const auto& ptr: gameObjects) {
            GameObjectID id = ptr->objectID;
            idsMap[id](*ptr);
        }  
    }
}
