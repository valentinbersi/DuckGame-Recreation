#pragma once

#include <memory>
#include <string>

#include "ActiveSocket.h"
#include "Background.h"
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
    /**
     * Send a Vector2 through the socket
     * @param vector the Vector2 to send
     */
    void sendVector2(const Vector2& vector);

    /**
     * Send a Segment2D through the socket
     * @param segment the Segment2D to send
     */
    void sendSegment(const Segment2D& segment);

    /**
     * Send a Rectangle through the socket
     * @param rectangle the Rectangle to send
     */
    void sendRectangle(const Rectangle& rectangle);

public:
    /**
     * Construct a new ServerSendProtocol object
     * @param socket the ActiveSocket to send data to
     */
    explicit ServerSendProtocol(ActiveSocket& socket);

    /**
     * Pass protocol to the message in order to send itself
     * @param mensaje the ServerMessage to send
     */
    void sendMessage(std::shared_ptr<ServerMessage>&& mensaje);

    /**
     * Send a lobby message to the client
     * @param roundEnded if the round has ended    * @param setEnded if the set has ended
     * @param gameEnded if the game has ended
     */
    void sendRoundData(bool roundEnded, bool setEnded, bool gameEnded);

    /**
     * Send a string through the socket
     * @param len the length of the string
     */
    void sendLen(u16 len);

    /**
     * Send a background through the socket
     * @param background the background to send
     */
    void sendBackground(BackgroundID background);

    /**
     * Send a duck data through the socket
     * @param objData the duck data to send
     */
    void sendDuckData(const DuckData& objData);

    /**
     *  Send an item data through the socket
     * @param objData  the item data to send
     */
    void sendItemData(const ItemData& objData);

    /**
     * Send a block through the socket
     * @param objData the block to send
     */
    void sendBlock(const SizedObjectData& objData);

    /**
     *  Send a list of duck data through the socket
     * @param matchID the id of the match
     * @param startGame  if the game has started
     * @param connectedPlayers  the amount of players connected
     * @param color1  the color of the first player
     * @param color2 the color of the second player
     * @param error the error message
     */
    void sendReplyMessage(u16 matchID, u8 startGame, u8 connectedPlayers, DuckData::Id color1,
                          DuckData::Id color2, const std::string& error);

    ~ServerSendProtocol() = default;
};
