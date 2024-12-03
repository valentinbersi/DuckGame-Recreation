#pragma once
#include <list>
#include <memory>
#include <string>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "GameStatus.h"
#include "ItemData.h"
#include "Math.h"
#include "ReceiveProtocol.h"
#include "ReplyMessage.h"
#include "Types.h"

/**
 *  Dedicated ReceiveProtocol for the client
 */
class ClientRecvProtocol: public ReceiveProtocol {
private:
    Vector2 recvVector2();

    Segment2D recvSegment();

    Rectangle recvRectangle();

    std::list<DuckData> recvDuckData();

    std::list<ItemData> recvItemData();

    std::list<SizedObjectData> recvBlockPositions();

public:
    /**
     * Construct a new ClientRecvProtocol object
     * @param socket the ActiveSocket to receive data from
     */
    explicit ClientRecvProtocol(ActiveSocket& socket);

    /**
     *  Receive a Reply from the server
     *  @return the ReplyMessage received
     */
    ReplyMessage recvReplyMessage();

    /**
     *  Receive a GameStatus from the server
     *  @return the GameStatus received
     */
    GameStatus recvGameStatus();

    /**
     * Default destructor
     */
    ~ClientRecvProtocol() = default;
};
