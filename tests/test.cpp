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
// using ::testing::AllOf;
// using ::testing::HasSubstr;
// using ::testing::ThrowsMessage;

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
