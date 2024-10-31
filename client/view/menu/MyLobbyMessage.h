#ifndef DUCKGAME_MYLOBBYMESSAGE_H
#define DUCKGAME_MYLOBBYMESSAGE_H

#include "Message.h"
#include "Types.h"

struct LobbyMessage_ : public Message {
    LobbyRequest request;
    std::string player1Name;
    std::string player2Name;
    u16 matchId;
    u8 playersNumber;
    std::string mapChosen;

    LobbyMessage_()
            : Message(MessageType::Lobby),
            request(),
            player1Name(""),
            player2Name(""),
            matchId(0),
            playersNumber(0),
            mapChosen("") {}

    LobbyMessage_(LobbyRequest request, std::string name1, std::string name2, u16 id, u8 count, std::string map)
            : Message(MessageType::Lobby),
            request(request),
            player1Name(name1),
            player2Name(name2),
            matchId(id),
            playersNumber(count),
            mapChosen(map) {}
};

#endif  // DUCKGAME_MYLOBBYMESSAGE_H
