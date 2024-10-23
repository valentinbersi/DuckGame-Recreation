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

#include <list>
#include <set>

TEST(ProtocolTest, ClientToServerSend) {

    ClientMessage clientMsg (MessageType::Input, InputAction::LEFT);

    std::thread client ([](){
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt (sktClient);
        ClientMessage clientMsg (MessageType::Input, InputAction::LEFT);
        sendProt.sendMessage(clientMsg);
    });

    ListenerSocket skt("8080");
    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt (peer);

    ClientMessage recvMsg = recvProt.receiveMessage();
    EXPECT_EQ(recvMsg.type, clientMsg.type);
    EXPECT_EQ(recvMsg.action, clientMsg.action);
    
    client.join();
    }

TEST(ProtocolTest, ClientToServerMultipleSends) {
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

    ListenerSocket skt("8080");
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

    ListenerSocket skt("8080");

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
