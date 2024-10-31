#pragma once

#include "Object.h"
#include "Player.h"

struct GameStatus;
typedef u16 PlayerID;

class GameController final: public Object {
    HashMap<PlayerID, Player*> players;

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
     * Does nothing on the game controller
     */
    void updateInternal(float delta) override;

    /**
     * Add a player to the match
     * @param playerID the id of the player to add
     */
    void addPlayer(PlayerID playerID);

    /**
     * Does nothing on the game controller
     * @return
     */
    GameStatus status() override;
};
