#pragma once

#include <string>

#include "Types.h"

struct GameInfo {
    u8 playersNumber;
    bool isNewGame;
    u16 matchID;

    GameInfo(): playersNumber(0), isNewGame(false), matchID(0) {}
};
