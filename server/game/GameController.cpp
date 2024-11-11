#include "GameController.h"

#include <iostream>
#include <memory>
#include <string>

#include "GameStatus.h"
#include "Platform.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...)                                          \
    std::make_unique<gameObject::EventHandler<GameController, __VA_ARGS__>>( \
            getReference<GameController>(), Function)

GameController::~GameController() = default;

void GameController::onTreeEntered(GameObject* object) {
    if (const auto collisionObject = dynamic_cast<CollisionObject*>(object);
        collisionObject != nullptr)
        collisionManager.addCollisionObject(collisionObject);
}

void GameController::onTreeExited(GameObject* object) {
    if (const auto collisionObject = dynamic_cast<CollisionObject*>(object);
        collisionObject != nullptr)
        collisionManager.removeCollisionObject(collisionObject);
}

GameController::GameController(): GameObject(nullptr) {
    connect(eventName(Events::TREE_ENTERED),
            eventHandler(&GameController::onTreeEntered, GameObject*));

    connect(eventName(Events::TREE_EXITED),
            eventHandler(&GameController::onTreeExited, GameObject*));

    addChild("Platform", new Platform);
}

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::update(const float delta) {
    collisionManager.processCollisions();
    std::cout << "The game is running" << delta << std::endl;
}

#define FULL_GAME "The game is full"

#define MAX_PLAYERS 4

void GameController::addPlayer(const PlayerID playerID) {
    const std::string id = std::to_string(playerID);

    if (players.size() >= MAX_PLAYERS)
        throw std::logic_error(FULL_GAME);

    const auto duckID = static_cast<DuckID>(players.size());

    const auto newPlayer = new Player(duckID);

    newPlayer->connect(eventName(Events::TREE_ENTERED),
                       eventHandler(&GameController::onTreeEntered, GameObject*));

    newPlayer->connect(eventName(Events::TREE_EXITED),
                       eventHandler(&GameController::onTreeExited, GameObject*));

    addChild(id, newPlayer);
    players[playerID] = newPlayer;
}

Player& GameController::getPlayer(const PlayerID playerID) const { return *players.at(playerID); }

GameStatus GameController::status() {
    GameStatus status;

    forAllChildren([&status](GameObject* child) {
        status.gameObjects.splice(status.gameObjects.end(),
                                  std::move(std::move(child->status()).gameObjects));
    });

    return status;
}
