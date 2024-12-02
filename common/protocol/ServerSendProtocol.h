#pragma once

#include <memory>
#include <string>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "ItemData.h"
#include "SendProtocol.h"
#include "Types.h"

// Forward declaration
struct ServerMessage;

/**
 *  Dedicated SendProtocol for the server
 */
class ServerSendProtocol final: public SendProtocol {
private:
    void sendVector2(const Vector2& vector);

    void sendSegment(const Segment2D& segment);

    void sendRectangle(const Rectangle& rectangle);

public:
    explicit ServerSendProtocol(ActiveSocket& socket);

    void sendMessage(std::shared_ptr<ServerMessage>&& mensaje);

    void sendRoundData(bool roundEnded, bool setEnded, bool gameEnded);

    void sendLen(u16 len);

    void sendDuckData(const DuckData& objData);

    void sendItemData(const ItemData& objData);

    void sendBlock(const SizedObjectData& objData);

    void sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers, DuckData::Id color1,
                          DuckData::Id color2, const std::string& error);

    ~ServerSendProtocol() = default;
};
