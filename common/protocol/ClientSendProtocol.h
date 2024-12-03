#pragma once
#include <memory>
#include <string>

#include "ActiveSocket.h"
#include "DuckData.h"
#include "SendProtocol.h"
#include "Types.h"

// Forward declaration
struct ClientMessage;

class ClientSendProtocol: public SendProtocol {
public:
    /**
     *  Construct a new ClientSendProtocol object
     *  @param socket the ActiveSocket to send data to
     */
    explicit ClientSendProtocol(ActiveSocket& socket);

    /**
     *  Pass protocol to the message in order to send itself
     *  @param message the ClientMessage to send
     */
    void sendMessage(std::unique_ptr<ClientMessage> message);

    /**
     *  Send a lobby message to the server
     *  @param type the type of the message (LobbyRequest)
     *  @param request the request of the message (NewMatch, JoinMatch, StartMatch)
     *  @param playerCount the amount of players connected locally
     *  @param matchId the id of the match to join, 0 if request is not JoinMatch
     */
    void sendLobbyMessage(u8 type, u8 request, u8 playerCount, u16 matchId);

    /**
     *  Send a game message to the server
     *  @param type the type of the message (GameRequest)
     *  @param action the action of the player registered
     *  @param player the player that sends the message (player 1 or 2, relevant if two players are
     * connected locally)
     */
    void sendGameMessage(u8 type, u8 action, u8 player);

    /**
     *  Default destructor
     */
    ~ClientSendProtocol() override = default;
};
