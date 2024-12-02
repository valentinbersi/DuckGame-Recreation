#include "GameController.h"

#include <ranges>
#include <string>
#include <utility>
#include <cstdint>

#include "Config.h"
#include "GameStatus.h"
#include "Layer.h"
#include "LevelData.h"
#include "RayCast.h"

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
            items.push_back(static_cast<Item*>(collisionObject));  // Safe to static cast here

        collisionManager.addCollisionObject(collisionObject);
    }

    if (const auto rayCast = dynamic_cast<RayCast*>(object); rayCast != nullptr)
        collisionManager.addRayCast(rayCast);
}

void GameController::onTreeExited(GameObject* object) {
    if (const auto collisionObject = dynamic_cast<CollisionObject*>(object);
        collisionObject != nullptr) {
        if (collisionObject->layers().test(Layer::Index::Item))
            items.remove(static_cast<Item*>(collisionObject));  // Safe to static cast here

        collisionManager.removeCollisionObject(collisionObject);
    }

    if (const auto rayCast = dynamic_cast<RayCast*>(object); rayCast != nullptr)
        collisionManager.removeRayCast(rayCast);
}

void GameController::loadLevel(const LevelData& level) {
    if (this->level != nullptr)
        removeChild("Level");

    this->level = new Level(level, players);
    addChild("Level", this->level);
}

void GameController::roundUpdate(u8 playerAlive, PlayerID playerID) {
    bool tie = false;
    u32 maxRoundsWon = 0;
    if (playerAlive <= 1) {
        ++roundsPlayed;
        roundEnded = true;
        if (playerAlive)  // hay un player vivo
            players.at(playerID)->winRound();

        maxRoundsWon = 0;
        for (const Player* player: players | std::views::values) {
            if (player->roundsWon() > maxRoundsWon) {
                // DuckData::Id playerID = static_cast<DuckData::Id>(id);
                tie = false;
                maxRoundsWon = player->roundsWon();

            } else if (player->roundsWon() == maxRoundsWon) {
                tie = true;
            }
        }
    }
    setEnded = ((roundsPlayed % Config::Match::rounds()) == 0) && roundsPlayed;
    _gameEnded = (setEnded && !tie && (maxRoundsWon >= Config::Match::pointsToWin())) || _gameEnded;
}

void GameController::clearState() {
    for (Player* player: players | std::views::values) player->reset();
    if (setEnded) {
        setEnded = false;
        roundsPlayed = 0;
    }
    items.clear();
}

#define PLAYER_ID "Player with id "
#define ALREADY_ADDED " already added"

GameController::AlreadyAddedPlayer::AlreadyAddedPlayer(const PlayerID id):
        std::logic_error(PLAYER_ID + std::to_string(id) + ALREADY_ADDED) {}

#define NOT_FOUND " was not found"

GameController::PlayerNotFound::PlayerNotFound(const PlayerID id):
        std::out_of_range(PLAYER_ID + std::to_string(id) + NOT_FOUND) {}

GameController::GameController(std::vector<LevelData>& levelsData):
        levelsData(levelsData),
        level(nullptr),
        roundsPlayed(0),
        roundEnded(false),
        setEnded(false),
        _gameEnded(false),
        mapSelector(0, static_cast<int>(levelsData.size()) - 1) {
    connect(Events::TreeEntered, eventHandler(&GameController::onTreeEntered, GameObject*));
    connect(Events::TreeExited, eventHandler(&GameController::onTreeExited, GameObject*));
}

void GameController::start() {
    loadLevel(levelsData[mapSelector()]);
    roundEnded = false;
}

void GameController::update(const float delta) {
    collisionManager.processCollisions(delta);
    u8 alivePlayers(0);
    PlayerID aliveID(0);
    for (auto& [id, player]: players) {
        player->clearInputs();
        if (!player->isDead()) {
            aliveID = id;
            ++alivePlayers;
        }
    }
    roundUpdate(alivePlayers, aliveID);
}

#define FULL_GAME "The game is full"

#define MAX_PLAYERS 4

#define PLAYER "Player "

DuckData::Id GameController::addPlayer(const PlayerID playerID) {
    if (players.contains(playerID))
        throw AlreadyAddedPlayer(playerID);

    const std::string id = std::to_string(playerID);

    if (players.size() >= MAX_PLAYERS)
        throw std::logic_error(FULL_GAME);

    const auto duckID = static_cast<DuckData::Id>(players.size());

    const auto newPlayer = new Player(duckID);

    addChild(PLAYER + id, newPlayer);
    players.emplace(playerID, newPlayer);
    return duckID;
}

void GameController::removePlayer(const PlayerID playerID) {
    if (const auto player = players.extract(playerID); player.empty())
        throw PlayerNotFound(playerID);

    (void)removeChild(PLAYER + std::to_string(playerID));
    players.erase(playerID);
    _gameEnded = players.empty();
}

Player& GameController::getPlayer(const PlayerID playerID) const { return *players.at(playerID); }

void GameController::giveItemToPlayer(const PlayerID playerID, const ItemID itemID) {
    if (players.contains(playerID))
        players.at(playerID)->setItem(itemID, Config::getDefaultAmmo(itemID), Force::Yes);
}

void GameController::giveFullAmmoToPlayer(const PlayerID playerID) {
    if (players.contains(playerID))
        players.at(playerID)->setAmmo(UINT8_MAX);
}

u8 GameController::playersCount() const { return players.size(); }

bool GameController::exceedsPlayerMax(const u8 playerAmount) const {
    return players.size() + playerAmount > MAX_PLAYERS;
}

void GameController::addToLevel(const std::string& nodeName,
                                std::unique_ptr<CollisionObject> physicObject) const {
    level->addChild(nodeName, std::move(physicObject));
}

GameStatus GameController::status() const {
    GameStatus status;
    status.roundEnded = roundEnded;
    status.gameEnded = _gameEnded;
    status.setEnded = setEnded;
    status.blockPositions = level->blockStatus();
    status.itemSpawnerPositions = level->itemSpawnerStatus();
    status.boxPositions = level->boxStatus();
    for (const auto& item: items) status.itemPositions.push_back(item->status());
    for (Player* player: players | std::views::values) status.ducks.push_back(player->status());
    return status;
}

bool GameController::gameEnded() const { return _gameEnded; }

bool GameController::roundInProgress() const { return !roundEnded; }

void GameController::startNewRound() { roundEnded = false; }

void GameController::loadNewState() {
    clearState();
    loadLevel(levelsData[mapSelector()]);
}

void GameController::endGame() { _gameEnded = true; }

void GameController::endRound() {
    // kills all players, no round point will be given.
    for (Player* player: players | std::views::values) player->kill();
}
