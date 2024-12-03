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
    /**
     * Receive a Vector2 from the server
     * @return  the Vector2 received
     */
    Vector2 recvVector2();

    /**
     * Receive a Segment2D from the server
     * @return the Segment2D received
     */
    Segment2D recvSegment();

    /**
     * Receive a Rectangle from the server
     * @return the Rectangle received
     */
    Rectangle recvRectangle();

    /**
     *  Receive a list of DuckData from the server
     * @return the list of DuckData received
     */
    std::list<DuckData> recvDuckData();

    /**
     * Receive a list of ItemData from the server
     * @return the list of ItemData received
     */
    std::list<ItemData> recvItemData();

    /**
     * Receive a list of SizedObjectData from the server
     * @return the list of SizedObjectData received
     */
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
