#include <list>
#include <memory>
#include <thread>

#include "gtest/gtest.h"

#include "ActiveSocket.h"
#include "ClientRecvProtocol.h"
#include "ClientSendProtocol.h"
#include "DuckData.h"
#include "GameMessage.h"
#include "GameStatus.h"
#include "ListenerSocket.h"
#include "LobbyMessage.h"
#include "Math.h"
#include "MessageType.h"
#include "ReplyMessage.h"
#include "ServerRecvProtocol.h"
#include "ServerSendProtocol.h"

TEST(ProtocolTest, LobbyToServerSend) {
    ListenerSocket skt("8080");
    std::string a = "Player1";
    std::string b = "Player2";
    LobbyMessage lobbyMsg(LobbyRequest::NEWMATCH, 2, a, b, 0);

    std::thread client([lobbyMsg]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        sendProt.sendMessage(std::make_unique<LobbyMessage>(lobbyMsg));
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt(peer);
    LobbyMessage recvMsg = recvProt.receiveLobbyMessage();

    ASSERT_TRUE(lobbyMsg == recvMsg);

    client.join();
}

TEST(ProtocolTest, LobbyToServerMultipleSends) {
    ListenerSocket skt("8080");
    std::list<LobbyMessage> list;
    std::string a = "Player1";
    std::string b = "Player2";
    std::string c = "Player3";
    std::string d = "Player4";
    std::string e = "Player5";
    std::string f = "Player6";
    std::string g = " ";

    list.push_back(LobbyMessage());
    list.push_back(LobbyMessage(LobbyRequest::NEWMATCH, 2, a, b, 0));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, c, d, 4281));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, e, f, 16678));
    list.push_back(LobbyMessage(LobbyRequest::STARTMATCH, 2, g, g, 31227));

    std::thread client([list]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        for (const auto& msg: list) {
            sendProt.sendMessage(std::make_unique<LobbyMessage>(msg));
        }
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt(peer);

    for (const auto& msg: list) {
        LobbyMessage recvMsg = recvProt.receiveLobbyMessage();
        ASSERT_TRUE(msg == recvMsg);
    }

    client.join();
}

TEST(ProtocolTest, MultiLoobySend) {
    ListenerSocket skt("8080");
    std::string a = "Player1";  
    std::string b = "Player2";
    std::string c = "Player3";
    std::string d = "Player4";
    LobbyMessage msg1(LobbyRequest::NEWMATCH, 2, a, b, 0);
    LobbyMessage msg2(LobbyRequest::JOINMATCH, 1, c, d, 4281);

    std::thread client1([msg1]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        sendProt.sendMessage(std::make_unique<LobbyMessage>(msg1));
    });

    std::thread client2([msg2]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        sendProt.sendMessage(std::make_unique<LobbyMessage>(msg2));
    });

    ActiveSocket peer1 = skt.accept();
    ServerRecvProtocol recvProt1(peer1);
    ActiveSocket peer2 = skt.accept();
    ServerRecvProtocol recvProt2(peer2);

    LobbyMessage recv1 = recvProt1.receiveLobbyMessage();
    LobbyMessage recv2 = recvProt2.receiveLobbyMessage();

    ASSERT_TRUE((msg1 == recv1 || msg1 == recv2) && (msg2 == recv1 || msg2 == recv2));

    client1.join();
    client2.join();
}

TEST(ProtocolTest, ServerToLobbySendReply) {
    ListenerSocket skt("8080");
    ReplyMessage replyMsg;

    std::thread client([replyMsg]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientRecvProtocol recvProt(sktClient);
        ReplyMessage recvMsg = recvProt.recvReplyMessage();
        ASSERT_TRUE(recvMsg == replyMsg);
    });

    ActiveSocket peer = skt.accept();
    ServerSendProtocol sendProt(peer);
    sendProt.sendMessage(std::make_shared<ReplyMessage>(replyMsg));

    client.join();
}

TEST(ProtocolTest, GameToServerOneMessage) {
    ListenerSocket skt("8080");
    GameMessage gameMsg(InputAction::LEFT_PRESSED, 1);

    std::thread client([gameMsg]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        sendProt.sendMessage(std::make_unique<GameMessage>(gameMsg));
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt(peer);
    GameMessage recvMsg = recvProt.receiveGameMessage();

    ASSERT_TRUE(gameMsg == recvMsg);

    client.join();
}

TEST(ProtocolTest, ServerToGameSendOneStatus) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->ducks.emplace_back(Vector2(0,0), DuckID::White, 10, ItemID::CowboyPistol, 0b100);
    status->blockPositions.emplace_back(0, 0);

    std::thread client([]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.recvGameStatus();
        ASSERT_EQ(recvStatus.ducks.size(), 1);
        ASSERT_EQ(recvStatus.blockPositions.size(), 1);
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

TEST(ProtocolTest, ServerToGameCorrectValues) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->ducks.emplace_back(Vector2(0, 0), DuckID::White, 10, ItemID::CowboyPistol, 0b100);
    status->blockPositions.emplace_back(0, 0);

    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        ASSERT_TRUE(statusRecv.ducks == status->ducks);
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

TEST(ProtocolTest, ServerToOneGameMultiSend) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->ducks.emplace_back( Vector2(42.6, 5.5134), DuckID::Grey, 8, ItemID::Ak47, 0b1 | 0b10);
    status->ducks.emplace_back( Vector2(0,0), DuckID::Orange, 1, ItemID::Banana, 0b1);
    status->ducks.emplace_back( Vector2(0, 5.5134), DuckID::White, 5, ItemID::DuelPistol, 0b1 | 0b10 | 0b100);
    status->ducks.emplace_back( Vector2(77.90845, 0.654), DuckID::Yellow, 10, ItemID::PewPewLaser, 0b1 | 0b10 | 0b1000);
    status->blockPositions.emplace_back(0, 0);
    status->blockPositions.emplace_back(100, 50);
    status->blockPositions.emplace_back(14.743, 66);

    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        auto it1 = status->ducks.begin();
        auto it2 = statusRecv.ducks.begin();
        while (it1 != status->ducks.end() && it2 != statusRecv.ducks.end()) {

            ASSERT_TRUE(*it1 == *it2);

            it1++;
            it2++;
        }
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
