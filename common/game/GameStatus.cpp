#include "GameStatus.h"

#include <utility>

GameStatus::GameStatus() : Message(MessageType::Game){} //Luego chequeamos.

GameStatus::GameStatus(GameStatus&& other) noexcept: Message(MessageType::Game), gameObjects(std::move(other.gameObjects)) {
}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    gameObjects = std::move(other.gameObjects);
    return *this;
}
