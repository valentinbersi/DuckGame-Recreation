#pragma once

#include "CollisionManager.h"
#include "Player.h"


struct Level;
struct GameStatus;
typedef u16 PlayerID;

class GameController final: public GameObject {
    HashMap<PlayerID, Player*> players;
    CollisionManager collisionManager;
    GameObject* level;

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
    /**
     * Exception thrown when trying to add a player that is already in the match
     */
    struct AlreadyAddedPlayer final: std::logic_error {
        /**
         * Construct an AlreadyAddedPlayer exception
         * @param id The id of the player that was already added
         */
        explicit AlreadyAddedPlayer(PlayerID id);
    };

    /**
     * Exception thrown when trying to remove a player that is not in the match
     */
    struct PlayerNotFound final: std::out_of_range {
        /**
         * Construct a PlayerNotFound exception
         * @param id The id of the player that was not found
         */
        explicit PlayerNotFound(PlayerID id);
    };

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
     * @throw AlreadyAddedPlayer if the player is already in the match
     */
    void addPlayer(PlayerID playerID);

    /**
     * Remove a player from the match
     * @param playerID the id of the player to remove
     * @throw PlayerNotFound if the player is not in the match
     */
    void removePlayer(PlayerID playerID);

    /**
     * Get a reference to a player by its id
     * @param playerID the id of the player to get
     * @return a reference to the player
     * @throw std::out_of_range if the player is not in the match
     */
    Player& getPlayer(PlayerID playerID) const;

    /**
     * Get the number of players in the match
     * @return the number of players in the match
     */
    u8 playersCount() const;

    /**
     * Load the level
     * @param level the level to load
     */
    void loadLevel(const Level& level);

    /**
     * Get the status of the game
     * @return the status of the game
     */
    GameStatus status() override;
};
