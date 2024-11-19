#pragma once
#include "ActiveSocket.h"
#include "DuckData.h"
#include "GameStatus.h"
#include "ReplyMessage.h"
#include "Math.h"
#include "ReceiveProtocol.h"
#include "Types.h"

/**
 *  Dedicated ReceiveProtocol for the client
 */
class ClientRecvProtocol: public ReceiveProtocol {
private:
    HashMap<GameObjectID, std::function<std::unique_ptr<GameObjectData>()>> idsMap;

    std::unique_ptr<GameObjectData> recvData();

    std::unique_ptr<GameObjectData> recvDuckData();

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
