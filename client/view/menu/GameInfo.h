#pragma once

#include "Types.h"

struct GameInfo {
    u8 playersNumber;
    std::string player1Name;
    std::string player2Name;
    bool isNewGame;
    std::string selectedMap;
    u16 matchID;

    GameInfo() : playersNumber(0), isNewGame(false), matchID(0) {
        player1Name = "";
        player2Name = "";
        selectedMap = "";
    }

//    QString infoString() const {
//        return QString("Jugadores: %1, Nombres: [%2, %3], Nuevo Juego: %4, Mapa: %5, ID de Partida: %6")
//                .arg(playersNumber)
//                .arg(player1Name)
//                .arg(player2Name)
//                .arg(isNewGame ? "Sí" : "No")
//                .arg(selectedMap)
//                .arg(matchID);
//    }
};


