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
#include "ItemData.h"
#include "ListenerSocket.h"
#include "LobbyMessage.h"
#include "Math.h"
#include "MessageType.h"
#include "ReplyMessage.h"
#include "ServerRecvProtocol.h"
#include "ServerSendProtocol.h"

TEST(ProtocolTest, LobbyToServerSend) {
    ListenerSocket skt("8080");
    LobbyMessage lobbyMsg(LobbyRequest::NEWMATCH, 2, 0);

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
    list.push_back(LobbyMessage());
    list.push_back(LobbyMessage(LobbyRequest::NEWMATCH, 2, 0));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, 4281));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, 16678));
    list.push_back(LobbyMessage(LobbyRequest::STARTMATCH, 2, 31227));

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
    LobbyMessage msg1(LobbyRequest::NEWMATCH, 2, 0);
    LobbyMessage msg2(LobbyRequest::JOINMATCH, 1, 4281);

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
    ReplyMessage replyMsg(12389, 1, 3, DuckData::Id::White, DuckData::Id::Yellow, "NO ERROR");

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

TEST(ProtocolTest, ServerToGameCorrectValues) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->ducks.emplace_back(Vector2(0, 0), DuckData::Id::White, DuckData::Direction::Center,
                               ItemID::CowboyPistol, 0b100, 5);
    status->itemPositions.emplace_back(
            ItemData(ItemID::Banana, Rectangle(Vector2(134, 4.7), Vector2(0, 3.124))));
    status->blockPositions.emplace_back(Rectangle(Vector2(0, 0), Vector2(0, 0)));
    status->itemSpawnerPositions.emplace_back(Rectangle(Vector2(23, 4), Vector2(6, 7)));
    status->boxPositions.emplace_back(Rectangle(Vector2(0, 78), Vector2(4.678, 0)));

    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        ASSERT_TRUE(*status == statusRecv);
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

TEST(ProtocolTest, ServerToOneGameFillStatus) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->ducks.emplace_back(Vector2(42.6, 5.5134), DuckData::Id::Grey, DuckData::Direction::Left,
                               ItemID::Ak47, 0b1 | 0b10, 56);
    status->ducks.emplace_back(Vector2(0, 0), DuckData::Id::Orange, DuckData::Direction::Right,
                               ItemID::Banana, 0b1, 29);
    status->ducks.emplace_back(Vector2(0, 5.5134), DuckData::Id::White, DuckData::Direction::Center,
                               ItemID::DuelPistol, 0b1 | 0b10 | 0b100, 5);
    status->ducks.emplace_back(Vector2(77.90845, 0.654), DuckData::Id::Yellow,
                               DuckData::Direction::Center, ItemID::PewPewLaser,
                               0b1 | 0b10 | 0b1000, 0);

    status->itemPositions.emplace_back(
            ItemData(ItemID::Banana, Rectangle(Vector2(134, 4.7), Vector2(0, 3.124))));
    status->itemPositions.emplace_back(
            ItemData(ItemID::CowboyPistol, Rectangle(Vector2(0, 0), Vector2(0, 0))));
    status->itemPositions.emplace_back(
            ItemData(ItemID::DuelPistol, Rectangle(Vector2(2, 3), Vector2(100, 50))));

    status->blockPositions.emplace_back(Rectangle(Vector2(0, 0), Vector2(0, 0)));
    status->blockPositions.emplace_back(Rectangle(Vector2(2, 3), Vector2(100, 50)));
    status->blockPositions.emplace_back(Rectangle(Vector2(13.0, 67.8), Vector2(8, 7)));

    status->itemSpawnerPositions.emplace_back(Rectangle(Vector2(33434.78, 123.8), Vector2(3, 4)));
    status->itemSpawnerPositions.emplace_back(Rectangle(Vector2(3234.49, 343.8), Vector2(7, 8)));

    status->boxPositions.emplace_back(Rectangle(Vector2(0, 70), Vector2(4.678, 0)));
    status->boxPositions.emplace_back(Rectangle(Vector2(100, 90), Vector2(56, 466)));

    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        ASSERT_TRUE(*status == statusRecv);
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
