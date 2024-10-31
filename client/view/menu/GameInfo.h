#pragma once

#include <QString>
#include "Types.h"

struct GameInfo {
    int playerCount;
    QString playerNames[2];
    bool isNewGame;
    QString selectedMap;
    u16 matchID;

    GameInfo() : playerCount(0), isNewGame(false), matchID(0) {
        playerNames[0] = "";
        playerNames[1] = "";
        selectedMap = "";
    }

    void setPlayerCount(int count) {
        if (count < 1 || count > 2) {
            throw std::invalid_argument("El número de jugadores debe ser 1 o 2.");
        }
        playerCount = count;
    }

    void setPlayerName(int index, const QString& name) {
        if (index < 0 || index > 1) {
            throw std::out_of_range("Índice fuera de rango para nombres de jugadores.");
        }
        playerNames[index] = name;
    }

    void setSelectedMap(const QString& map) {
        selectedMap = map;
    }

    void setIsNewGame(bool isNew) {
        isNewGame = isNew;
    }

    void setMatchID(u16 id) {
        matchID = id;
    }

    QString infoString() const {
        return QString("Jugadores: %1, Nombres: [%2, %3], Nuevo Juego: %4, Mapa: %5, ID de Partida: %6")
                .arg(playerCount)
                .arg(playerNames[0])
                .arg(playerNames[1])
                .arg(isNewGame ? "Sí" : "No")
                .arg(selectedMap)
                .arg(matchID);
    }
};


