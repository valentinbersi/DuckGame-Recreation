#include "GameController.h"

#include <ranges>
#include <string>
#include <utility>

#include "GameStatus.h"
#include "Layer.h"
#include "LevelData.h"
#include "SpawnPoint.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...)                                                               \
    gameObject::EventHandler<GameController, __VA_ARGS__>::create(getReference<GameController>(), \
                                                                  Function)

GameController::~GameController() = default;

void GameController::onTreeEntered(GameObject* object) {
    if (const auto collisionObject = dynamic_cast<CollisionObject*>(object);
        collisionObject != nullptr) {
        if (collisionObject->layers().test(Layer::Index::Item))
            items.push_back(static_cast<Item*>(collisionObject));

        collisionManager.addCollisionObject(collisionObject);
    }
}

void GameController::onTreeExited(GameObject* object) {
    if (const auto collisionObject = dynamic_cast<CollisionObject*>(object);
        collisionObject != nullptr) {
        if (collisionObject->layers().test(Layer::Index::Item))
            items.remove(static_cast<Item*>(collisionObject));

        collisionManager.removeCollisionObject(collisionObject);
    }
}

#define PLAYER_ID "Player with id "
#define ALREADY_ADDED " already added"

GameController::AlreadyAddedPlayer::AlreadyAddedPlayer(const PlayerID id):
        std::logic_error(PLAYER_ID + std::to_string(id) + ALREADY_ADDED) {}

#define NOT_FOUND " was not found"

GameController::PlayerNotFound::PlayerNotFound(const PlayerID id):
        std::out_of_range(PLAYER_ID + std::to_string(id) + NOT_FOUND) {}

GameController::GameController(): level(nullptr) {
    connect(Events::TreeEntered, eventHandler(&GameController::onTreeEntered, GameObject*));

    connect(Events::TreeExited, eventHandler(&GameController::onTreeExited, GameObject*));

    // addChild("Platform", new Platform({0, 600}, 1000, 200));  // This simulated loading a level
    //  addChild("Platform2", new Platform({400, 400}, 50, 200));  // This simulated loading a level
}

void GameController::start() {}

void GameController::update(const float delta) {
    collisionManager.processCollisions(delta);
    for (Player* player: players | std::views::values) player->clearInputs();
}

#define FULL_GAME "The game is full"

#define MAX_PLAYERS 4

#define PLAYER "Player "

void GameController::addPlayer(const PlayerID playerID) {
    if (players.contains(playerID))
        throw AlreadyAddedPlayer(playerID);

    const std::string id = std::to_string(playerID);

    if (players.size() >= MAX_PLAYERS)
        throw std::logic_error(FULL_GAME);

    const auto duckID = static_cast<DuckData::Id>(players.size());

    const auto newPlayer = new Player(duckID);

    newPlayer->connect(Events::TreeEntered,
                       eventHandler(&GameController::onTreeEntered, GameObject*));

    newPlayer->connect(Events::TreeExited,
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

void GameController::loadLevel(const LevelData& level) {
    if (this->level != nullptr)
        removeChild("Level");

    this->level = new Level(level);

    this->level->connect(Events::TreeEntered,
                         eventHandler(&GameController::onTreeEntered, GameObject*));
    this->level->connect(Events::TreeExited,
                         eventHandler(&GameController::onTreeExited, GameObject*));

    addChild("Level", this->level);
}

GameStatus GameController::status() const {
    GameStatus status;
    status.blockPositions = level->blockStatus();
    status.itemSpawnerPositions = level->itemSpawnerStatus();
    for (const auto& item: items) status.itemPositions.push_back(item->status());
    for (Player* player: players | std::views::values) status.ducks.push_back(player->status());
    return status;
}
