#include "ClientRecvProtocol.h"

#include "ReplyMessage.h"

ClientRecvProtocol::ClientRecvProtocol(ActiveSocket& socket): ReceiveProtocol(socket) {}

Vector2 ClientRecvProtocol::recvVector2() {
    float x = Math::integerToFloat(recvInt());
    float y = Math::integerToFloat(recvInt());
    return Vector2(x, y);
}

Rectangle ClientRecvProtocol::recvRectangle() {
    Vector2 position = recvVector2();
    Vector2 size = recvVector2();
    return Rectangle(position, size);
}

std::list<DuckData> ClientRecvProtocol::recvDuckData() {
    u16 size = recvShort();
    std::list<DuckData> ducks;
    for (u16 i(0); i < size; ++i) {
        DuckData::Id duckID = static_cast<DuckData::Id>(recvByte());
        DuckData::Direction direction = static_cast<DuckData::Direction>(recvByte());
        u8 gunID = static_cast<ItemID>(recvByte());
        u16 actions = recvShort();
        u32 roundsWon = recvInt();
        Vector2 position = recvVector2();
        ducks.emplace_back(position, duckID, direction, gunID, actions, roundsWon);
    }
    return ducks;
}

std::list<ItemData> ClientRecvProtocol::recvItemData() {
    u16 size = recvShort();
    std::list<ItemData> items;
    for (u16 i(0); i < size; ++i) {
        u8 id = recvByte();
        items.emplace_back(static_cast<ItemID>(id), recvRectangle());
    }
    return items;
}

std::list<SizedObjectData> ClientRecvProtocol::recvBlockPositions() {
    u16 size = recvShort();
    std::list<SizedObjectData> blockPositions;
    for (u16 i(0); i < size; ++i) {
        blockPositions.emplace_back(recvRectangle());
    }
    return blockPositions;
}

GameStatus ClientRecvProtocol::recvGameStatus() {
    GameStatus status;
    recvByte();  // type
    status.roundEnded = recvByte();
    status.setEnded = recvByte();
    status.gameEnded = recvByte();
    status.ducks = recvDuckData();
    status.itemPositions = recvItemData();
    status.blockPositions = recvBlockPositions();
    status.itemSpawnerPositions = recvBlockPositions();
    status.boxPositions = recvBlockPositions();
    return status;
}

ReplyMessage ClientRecvProtocol::recvReplyMessage() {
    recvByte();  // type
    u16 matchID = recvShort();
    u8 startGame = recvByte();
    u8 connectedPlayers = recvByte();
    DuckData::Id color1 = static_cast<DuckData::Id>(recvByte());
    DuckData::Id color2 = static_cast<DuckData::Id>(recvByte());
    std::string error = recvString();

    return ReplyMessage(matchID, startGame, connectedPlayers, color1, color2, error);
}
