#pragma once

#include "CollisionManager.h"
#include "Player.h"

struct GameStatus;
typedef u16 PlayerID;

class GameController final: public GameObject {
    HashMap<PlayerID, Player*> players;
    CollisionManager collisionManager;

    /**
     * GameController handler for tree entered event
     * @param object The child that was added
     */
    void onTreeEntered(GameObject* object) override;

    /**
     * GameController handler for tree entered event
     * @param object The child that was removed
     */
    void onTreeExited(GameObject* object) override;

public:
    GameController();
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;
    GameController(GameController&&) noexcept = delete;
    GameController& operator=(GameController&&) noexcept = delete;
    ~GameController() override;

    /**
     * Start the match
     */
    void start() override;

    /**
     * Update the match
     * @param delta Time since the last update
     */
    void update(float delta) override;

    /**
     * Add a player to the match
     * @param playerID the id of the player to add
     */
    void addPlayer(PlayerID playerID);

    /**
     * Get a reference to a player by its id
     * @param playerID the id of the player to get
     * @return a reference to the player
     */
    Player& getPlayer(PlayerID playerID) const;

    /**
     * Does nothing on the game controller
     * @return
     */
    GameStatus status() override;
};
