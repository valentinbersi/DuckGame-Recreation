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
#include <memory>

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

std::unique_ptr<GameObjectData> creatDuckData(){
    Vector2 vecdef(1,2);
    float rotation = 0;
    DuckID duckID = DuckID::RED;
    u8 life = 100;
    GunID gunID = GunID::Ak47; 
    u8 actions = 0b1 | 0b01 | 0b001 | 0b0001 | 0b00001;
    return std::make_unique<DuckData>(vecdef,rotation,duckID,life, 
                                    std::make_unique<EquippedGunData>(gunID), actions);
}

TEST(ProtocolTest, ServerToClientSend){
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->addObject(std::move(creatDuckData()));

    std::thread client ([](){
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.receiveMessage();
        ASSERT_TRUE(recvStatus.gameObjects().size() == 1);

    });
    
    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    // EXPECT_EQ(recvMsg.action, clientMsg.action);
    
    client.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
