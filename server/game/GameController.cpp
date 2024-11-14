#include "GameController.h"

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

#define PLAYER_ID "Player with id "
#define ALREADY_ADDED " already added"

GameController::AlreadyAddedPlayer::AlreadyAddedPlayer(const PlayerID id):
        std::logic_error(PLAYER_ID + std::to_string(id) + ALREADY_ADDED) {}

#define NOT_FOUND " was not found"

GameController::PlayerNotFound::PlayerNotFound(const PlayerID id):
        std::out_of_range(PLAYER_ID + std::to_string(id) + NOT_FOUND) {}

GameController::GameController(): GameObject(nullptr) {
    connect(eventName(Events::TREE_ENTERED),
            eventHandler(&GameController::onTreeEntered, GameObject*));

    connect(eventName(Events::TREE_EXITED),
            eventHandler(&GameController::onTreeExited, GameObject*));

    addChild("Platform", new Platform);  // This simulated loading a level
}

void GameController::start() {}

void GameController::update(const float delta) { collisionManager.processCollisions(delta); }

#define FULL_GAME "The game is full"

#define MAX_PLAYERS 4

#define PLAYER "Player "

void GameController::addPlayer(const PlayerID playerID) {
    if (players.contains(playerID))
        throw AlreadyAddedPlayer(playerID);

    const std::string id = std::to_string(playerID);

    if (players.size() >= MAX_PLAYERS)
        throw std::logic_error(FULL_GAME);

    const auto duckID = static_cast<DuckID>(players.size());

    const auto newPlayer = new Player(duckID);

    newPlayer->connect(eventName(Events::TREE_ENTERED),
                       eventHandler(&GameController::onTreeEntered, GameObject*));

    newPlayer->connect(eventName(Events::TREE_EXITED),
                       eventHandler(&GameController::onTreeExited, GameObject*));

    addChild(PLAYER + id, newPlayer);
    players.emplace(playerID, newPlayer);
}

void GameController::removePlayer(const PlayerID playerID) {
    if (const auto player = players.extract(playerID); player.empty())
        throw PlayerNotFound(playerID);

    (void)removeChild(PLAYER + std::to_string(playerID));
}

Player& GameController::getPlayer(const PlayerID playerID) const { return *players.at(playerID); }

u8 GameController::playersCount() const { return players.size(); }

GameStatus GameController::status() {
    GameStatus status;

    forAllChildren([&status](GameObject* child) {
        status.gameObjects.splice(status.gameObjects.end(),
                                  std::move(std::move(child->status()).gameObjects));
    });

    return status;
}
