
#include "ServerSendProtocol.h"
#include <cstring>
#include "gtest/gtest.h"

ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ServerSendProtocol::sendPlayerData(std::vector<char>& playerData){
    for (size_t i=0; i<playerData.size();i++){
        if (i==2 || i==6 || i==8){
            u32 valor;
            std::memcpy(&valor, &playerData[i], sizeof(u32));
            sendInt(valor);
        }else{
            sendByte(playerData[i]);
        }
    }
}

void ServerSendProtocol::sendData(std::vector<char>& data){
    //Por ahora solo serian los datos de los players/patos
    //Posibblemente esto se convierta en un diccionario pero por ahora definimoslo asi.
    sendPlayerData(data);
}


void ServerSendProtocol::sendMessage(std::shared_ptr<GameStatus>& status) {
    const auto& gameObjects = status->gameObjects();
    sendShort(gameObjects.size());
    for(auto iter=gameObjects.begin(); iter!=gameObjects.end(); ++iter){
        if (*iter){
            std::vector<char> data = (*iter)->data();
            sendData(data);
            continue;
        }
        GTEST_LOG_(INFO) << "ESTA NULO EL PUNTERO????";
    }
}
