#ifndef DUCKGAME_MYLOBBYMESSAGE_H
#define DUCKGAME_MYLOBBYMESSAGE_H

#include "Message.h"
#include "Types.h"

struct LobbyMessage_ : public Message {
    LobbyRequest request;
    std::string player1Name;
    std::string player2Name;
    u16 matchId;
    u8 playerCount;
    std::string mapChosen;

    LobbyMessage_()
            : Message(MessageType::Lobby),
            request(),
            player1Name(""),
            player2Name(""),
            matchId(0),
            playerCount(0),
            mapChosen("") {}

    LobbyMessage_(LobbyRequest request, std::string name1, std::string name2, u16 id, u8 count, std::string map)
            : Message(MessageType::Lobby),
            request(request),
            player1Name(name1),
            player2Name(name2),
            matchId(id),
            playerCount(count),
            mapChosen(map) {}

    [[nodiscard]] LobbyRequest getRequest() const { return request; }
    void setRequest(LobbyRequest req) { request = req; }

    [[nodiscard]] std::string getPlayer1Name() const { return player1Name; }
    void setPlayer1Name(const std::string& name) { player1Name = name; }

    [[nodiscard]] std::string getPlayer2Name() const { return player2Name; }
    void setPlayer2Name(const std::string& name) { player2Name = name; }

    [[nodiscard]] u16 getMatchId() const { return matchId; }
    void setMatchId(u16 id) { matchId = id; }

    [[nodiscard]] u8 getPlayerCount() const { return playerCount; }
    void setPlayerCount(u8 count) { playerCount = count; }

    [[nodiscard]] std::string getMapChosen() const { return mapChosen; }
    void setMapChosen(const std::string& map) { mapChosen = map; }
};

#endif  // DUCKGAME_MYLOBBYMESSAGE_H
