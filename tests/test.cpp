#include "gtest/gtest.h"

#include "ServerRecvProtocol.h"
#include "ServerSendProtocol.h"

#include "ClientSendProtocol.h"
#include "ClientRecvProtocol.h"

#include "ClientMessage.h"
#include "MessageType.h"

#include "ActiveSocket.h"
#include "ListenerSocket.h"
#include <thread>

#include "DuckData.h"

#include <list>
#include "Math.h"
#include <memory>

std::unique_ptr<GameObjectData> creatDuckData(float x, float y, float rot, DuckID d_id, u8 d_life,
                                                GunID g_id, u16 d_actions){
    Vector2 vecdef(x,y);
    float rotation = rot;
    DuckID duckID = d_id;
    u8 life = d_life;
    GunID gunID = g_id; 
    u16 actions = d_actions;
    return std::make_unique<DuckData>(vecdef,rotation,duckID,life, 
                                    std::make_unique<EquippedGunData>(gunID), actions);
}

TEST(ProtocolTest, ClientToServerSend) {
    ListenerSocket skt("8080");
    ClientMessage clientMsg (MessageType::Input, InputAction::LEFT);

    std::thread client ([](){
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt (sktClient);
        ClientMessage clientMsg (MessageType::Input, InputAction::LEFT);
        sendProt.sendMessage(clientMsg);
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt (peer);

    ClientMessage recvMsg = recvProt.receiveMessage();
    EXPECT_EQ(recvMsg.type, clientMsg.type);
    EXPECT_EQ(recvMsg.action, clientMsg.action);
    
    client.join();
    }

TEST(ProtocolTest, ClientToServerMultipleSends) {
    ListenerSocket skt("8080");
    std::list<ClientMessage> list;
    for(int i=0; i<50; i++){
        list.push_back(ClientMessage(MessageType::Input, InputAction::LEFT));
        list.push_back(ClientMessage(MessageType::Input, InputAction::RIGHT));
    }

    std::thread client ([list](){
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt (sktClient);
        for(auto iter=list.begin(); iter!=list.end(); iter++){
            sendProt.sendMessage(*iter);
        }
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt (peer);

    for (auto iter=list.begin(); iter!=list.end(); iter++){
        ClientMessage recvMsg = recvProt.receiveMessage();
        EXPECT_EQ(iter->type, recvMsg.type);
        EXPECT_EQ(iter->action, recvMsg.action);
    }
    
    client.join();
}

TEST(ProtocolTest, MultiClientSend) {
    ListenerSocket skt("8080");
    ClientMessage msg1 (MessageType::Input, InputAction::LEFT);
    ClientMessage msg2 (MessageType::Input, InputAction::RIGHT);

    std::thread client1 ([msg1](){
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt (sktClient);
        sendProt.sendMessage(msg1);
    });

    std::thread client2 ([msg2](){
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt (sktClient);
        sendProt.sendMessage(msg2);
    });

    ActiveSocket peer1 = skt.accept();
    ServerRecvProtocol recvProt1 (peer1);
    ActiveSocket peer2 = skt.accept();
    ServerRecvProtocol recvProt2 (peer2);
    ClientMessage recv1 = recvProt1.receiveMessage();
    ClientMessage recv2 = recvProt2.receiveMessage();

    if (recv1.type == msg1.type && recv1.action == msg1.action ){
        ASSERT_TRUE(recv2.type == msg2.type && recv2.action ==msg2.action);
    }else{
        ASSERT_TRUE(recv1.type == msg2.type && recv1.action ==msg2.action);
    }

    client1.join();
    client2.join();
}

TEST(ProtocolTest, ServerToClientSendOneStatus){
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(creatDuckData(0,0,0,DuckID::White, 10, GunID::CowboyPistol, 0b100));

    std::thread client ([](){
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.receiveMessage();
        ASSERT_TRUE(recvStatus.gameObjects.size() == 1);

    });
    
    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);
    
    client.join();
}

TEST(ProtocolTest, ServerToClientCorrectValues){
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(creatDuckData(0,0,0,DuckID::White, 10, GunID::CowboyPistol, 0b100));

    std::thread client ([status](){
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.receiveMessage();
        std::unique_ptr<GameObjectData> data = std::move(recvStatus.gameObjects.front());
        const DuckData* duckdata = dynamic_cast<const DuckData*>(&*data);
        const DuckData* originalData = dynamic_cast<const DuckData*>(&*status->gameObjects.front());

        //CheckIDS
        ASSERT_TRUE(duckdata->objectID == originalData->objectID);
        ASSERT_TRUE(duckdata->object2DID == originalData->object2DID);
        ASSERT_TRUE(duckdata->duckID == originalData->duckID);
        ASSERT_TRUE(duckdata->gun->gunID == originalData->gun->gunID);

        //Check vector traits
        ASSERT_TRUE(duckdata->position == originalData->position);
        ASSERT_TRUE(duckdata->rotation == originalData->rotation);

        //Check DuckTraits
        ASSERT_TRUE(duckdata->life == originalData->life);
        ASSERT_TRUE(duckdata->extraData == originalData->extraData);
    });
    
    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);
    
    client.join();
}

TEST(ProtocolTest, ServerToClientFloatCheck){
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(creatDuckData(42.7, 5.5134, 47.89, DuckID::Grey,
                                                    100, GunID::Ak47, 0b1|0b10));

    std::thread client ([status](){
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.receiveMessage();

        std::unique_ptr<GameObjectData> data = std::move(recvStatus.gameObjects.front());
        const DuckData* duckdata = dynamic_cast<const DuckData*>(&*data);
        const DuckData* originalData = dynamic_cast<const DuckData*>(&*status->gameObjects.front());

        //Check vector traits
        ASSERT_TRUE(duckdata->position == originalData->position);
        ASSERT_TRUE(Math::isEqualAprox(duckdata->rotation, originalData->rotation));
    });
    
    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);
    
    client.join();
}

TEST(ProtocolTest, ServerToOneClientMultiSend){
        ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(creatDuckData(42.7, 5.5134, 47.89, DuckID::Grey,
                                                    8, GunID::Ak47, 0b1|0b10));
    status->gameObjects.emplace_back(creatDuckData(0, 0, 45, DuckID::Orange,
                                                    1, GunID::Banana, 0b1));
    status->gameObjects.emplace_back(creatDuckData(0, 5.5134, 0, DuckID::White,
                                                    5, GunID::DuelPistol, 0b1|0b10|0b100));
    status->gameObjects.emplace_back(creatDuckData(77.90845, 0.654, 90, DuckID::Yellow,
                                                    10, GunID::PewPewLaser, 0b1|0b10|0b1000));


    std::thread client ([status](){
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.receiveMessage();
        auto it1 = status->gameObjects.begin();
        auto it2 = recvStatus.gameObjects.begin();
        while(it1!=status->gameObjects.end() && it2!=recvStatus.gameObjects.end()){

            const DuckData* originalData = dynamic_cast<const DuckData*>(&**it1);
            const DuckData* duckdata = dynamic_cast<const DuckData*>(&**it2);

             //CheckIDS
            ASSERT_TRUE(duckdata->objectID == originalData->objectID);
            ASSERT_TRUE(duckdata->object2DID == originalData->object2DID);
            ASSERT_TRUE(duckdata->duckID == originalData->duckID);
            ASSERT_TRUE(duckdata->gun->gunID == originalData->gun->gunID);

            //Check vector traits
            ASSERT_TRUE(duckdata->position == originalData->position);
            ASSERT_TRUE(Math::isEqualAprox(duckdata->rotation,originalData->rotation));

            //Check DuckTraits
            ASSERT_TRUE(duckdata->life == originalData->life);
            ASSERT_TRUE(duckdata->extraData == originalData->extraData);

            it1++;
            it2++;
        }

    });
    
    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);
    
    client.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
