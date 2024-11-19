#pragma once

#include "Types.h"

struct GameInfo {
    u8 playersNumber;
    std::string player1Name;
    std::string player2Name;
    bool isNewGame;
    std::string selectedMap;
    u16 matchID;

    GameInfo(): playersNumber(0), isNewGame(false), matchID(0) {
        player1Name = "";
        player2Name = "";
        selectedMap = "";
    }
};
