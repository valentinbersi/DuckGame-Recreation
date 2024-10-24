
#include "ServerSendProtocol.h"
#include <cstring>
#include "gtest/gtest.h"

ServerSendProtocol::ServerSendProtocol(ActiveSocket& socket): SendProtocol(socket) {}

void ServerSendProtocol::sendPlayerData(std::vector<char>& playerData){
    char* ptr = playerData.data();
    ptr+=2;
    for (size_t i=2; i<playerData.size();i++){
        if (i==2 || i==6 || i==10){
            int* ptrAux = reinterpret_cast<int*>(ptr);
            sendInt(*ptrAux);
            i+=3;
            ptr+=3;
        }else{
            sendByte(*ptr);
        }
        ptr++;
    }
}

void ServerSendProtocol::sendData(std::vector<char>& data){
    //Por ahora solo serian los datos de los players/patos
    sendByte(data[0]);
    sendByte(data[1]);
    //Posibblemente esto se convierta en un diccionario pero por ahora definimoslo asi.
    sendPlayerData(data);
}


void ServerSendProtocol::sendMessage(std::shared_ptr<GameStatus>& status) {
    const auto& gameObjects = status->gameObjects();
    sendShort(gameObjects.size());
    for(auto iter=gameObjects.begin(); iter!=gameObjects.end(); ++iter){
        std::vector<char> data = (*iter)->data();
        sendData(data);
    }
}
