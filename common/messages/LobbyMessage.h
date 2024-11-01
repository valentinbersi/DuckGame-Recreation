
#pragma once
#include <string>

#include "Message.h"
#include "Types.h"

struct LobbyMessage : public Message {
    LobbyRequest request;
    u8 playerCount;
    std::string player1Name;
    std::string player2Name;
    u16 matchId;
   
    LobbyMessage()
            : Message(MessageType::Lobby),
            request(),
            player1Name(""),
            player2Name(""),
            matchId(0),
            playerCount(0) {}

    LobbyMessage(LobbyRequest request, u8 count, std::string name1, std::string name2, u16 id)
            : Message(MessageType::Lobby),
            request(request),
            playerCount(count),
            player1Name(name1),
            player2Name(name2),
            matchId(id) {}

    ~LobbyMessage() = default;
};