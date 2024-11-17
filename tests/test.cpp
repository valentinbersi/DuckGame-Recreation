#include <list>
#include <memory>
#include <thread>

#include "gtest/gtest.h"

#include "ActiveSocket.h"
#include "ListenerSocket.h"

#include "GameStatus.h"
#include "ReplyMessage.h"
#include "GameMessage.h"
#include "LobbyMessage.h"

#include "DuckData.h"
#include "Math.h"
#include "MessageType.h"

#include "ClientRecvProtocol.h"
#include "ClientSendProtocol.h"
#include "ServerRecvProtocol.h"
#include "ServerSendProtocol.h"

std::unique_ptr<GameObjectData> creatDuckData(float x, float y, float rot, DuckID d_id, u8 d_life,
                                              GunID g_id, u16 d_actions) {
    Vector2 vecdef(x, y);
    float rotation = rot;
    DuckID duckID = d_id;
    u8 life = d_life;
    GunID gunID = g_id;
    u16 actions = d_actions;
    return std::make_unique<DuckData>(vecdef, rotation, duckID, life,
                                      std::make_unique<EquippedGunData>(gunID), actions);
}

TEST(ProtocolTest,  LobbyToServerSend) {
    ListenerSocket skt("8080");
    LobbyMessage lobbyMsg(LobbyRequest::NEWMATCH, 2, "Player1", "Player2", 0);

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
    list.push_back(LobbyMessage(LobbyRequest::NEWMATCH, 2, "Player1", "Player2", 0));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, "Andres", "Camilo", 4281));
    list.push_back(LobbyMessage(LobbyRequest::JOINMATCH, 1, "Valentin", "Tomas", 16678));
    list.push_back(LobbyMessage(LobbyRequest::STARTMATCH, 2, "", "", 31227));

    std::thread client([list]() {
        ActiveSocket sktClient("localhost", "8080");
        ClientSendProtocol sendProt(sktClient);
        for (const auto& msg : list) {
            sendProt.sendMessage(std::make_unique<LobbyMessage>(msg));
        }
    });

    ActiveSocket peer = skt.accept();
    ServerRecvProtocol recvProt(peer);

    for (const auto& msg : list) {
        LobbyMessage recvMsg = recvProt.receiveLobbyMessage();
        ASSERT_TRUE(msg == recvMsg);
    }

    client.join();
}

TEST(ProtocolTest, MultiLoobySend) {
    ListenerSocket skt("8080");
    LobbyMessage msg1(LobbyRequest::NEWMATCH, 2, "Player1", "Player2", 0);
    LobbyMessage msg2(LobbyRequest::JOINMATCH, 1, "Andres", "", 4281);

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
    status->gameObjects.emplace_back(
            creatDuckData(0, 0, 0, DuckID::White, 10, GunID::CowboyPistol, 0b100));

    std::thread client([]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus recvStatus = recvProtocol.recvGameStatus();
        ASSERT_TRUE(recvStatus.gameObjects.size() == 1);
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

TEST(ProtocolTest, ServerToGameCorrectValues) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(
            creatDuckData(0, 0, 0, DuckID::White, 10, GunID::CowboyPistol, 0b100));

    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        std::unique_ptr<GameObjectData> data = std::move(statusRecv.gameObjects.front());

        const DuckData* duckdata = dynamic_cast<const DuckData*>(&*data);
        const DuckData* originalData = dynamic_cast<const DuckData*>(&*status->gameObjects.front());
        ASSERT_TRUE(*duckdata == *originalData);
    });

    ActiveSocket skt = peer.accept();
    ServerSendProtocol sendProtocol(skt);
    sendProtocol.sendMessage(status);

    client.join();
}

TEST(ProtocolTest, ServerToOneGameMultiSend) {
    ListenerSocket peer("8080");

    std::shared_ptr<GameStatus> status = std::make_shared<GameStatus>();
    status->gameObjects.emplace_back(
            creatDuckData(42.7, 5.5134, 47.89, DuckID::Grey, 8, GunID::Ak47, 0b1 | 0b10));
    status->gameObjects.emplace_back(
            creatDuckData(0, 0, 45, DuckID::Orange, 1, GunID::Banana, 0b1));
    status->gameObjects.emplace_back(
            creatDuckData(0, 5.5134, 0, DuckID::White, 5, GunID::DuelPistol, 0b1 | 0b10 | 0b100));
    status->gameObjects.emplace_back(creatDuckData(77.90845, 0.654, 90, DuckID::Yellow, 10,
                                                   GunID::PewPewLaser, 0b1 | 0b10 | 0b1000));


    std::thread client([status]() {
        ActiveSocket clientSkt("localhost", "8080");
        ClientRecvProtocol recvProtocol(clientSkt);
        GameStatus statusRecv = recvProtocol.recvGameStatus();
        auto it1 = status->gameObjects.begin();
        auto it2 = statusRecv.gameObjects.begin();
        while (it1 != status->gameObjects.end() && it2 != statusRecv.gameObjects.end()) {

            const DuckData* originalData = dynamic_cast<const DuckData*>(&**it1);
            const DuckData* duckdata = dynamic_cast<const DuckData*>(&**it2);

            ASSERT_TRUE(*duckdata == *originalData);

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
