#pragma once

#include <list>

#include "DuckData.h"
#include "ItemData.h"
#include "ServerMessage.h"
#include "SizedObjectData.h"

/**
 * A struct with the current game status.
 */
struct GameStatus final: ServerMessage {
    GameStatus();
    GameStatus(const GameStatus& other);
    GameStatus& operator=(const GameStatus& other);
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;
    bool operator==(const GameStatus& other) const;

    bool roundEnded;
    bool gameEnded;
    bool setEnded;
    std::list<DuckData> ducks;
    std::list<ItemData> itemPositions;
    std::list<SizedObjectData> blockPositions;
    std::list<SizedObjectData> itemSpawnerPositions;
    std::list<SizedObjectData> boxPositions;

    /**
     * Send the GameStatus to the Client.
     * @param serverProtocol the protocol used to send to client.
     */
    void send(ServerSendProtocol& serverProtocol) override;

private:
    /**
     * Send a list of type T to the Client.
     * @param serverProtocol the protocol used to send to client.
     * @param list the list to send.
     * @param sendFunc the function of the serverProtocol to send the specific type of list.
     */
    template <typename T>
    void sendList(ServerSendProtocol& serverProtocol, const std::list<T>& list,
                  void (ServerSendProtocol::*sendFunc)(const T&));
};
