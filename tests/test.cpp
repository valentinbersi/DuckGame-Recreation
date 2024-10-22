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

// using ::testing::AllOf;
// using ::testing::HasSubstr;
// using ::testing::ThrowsMessage;

TEST(StandardProtocolTest, ClientToServerSendBytes) {

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
    
    }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
