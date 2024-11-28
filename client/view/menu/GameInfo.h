#pragma once

#include <string>

#include "Types.h"

struct GameInfo {
    u8 playersNumber;
    bool isNewGame;
    u16 matchID;
    DuckData::Id Duck1Color = DuckData::Id::None;
    DuckData::Id Duck2Color = DuckData::Id::None;

    GameInfo(): playersNumber(0), isNewGame(false), matchID(0) {}
};
