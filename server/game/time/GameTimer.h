#pragma once

#include "GameObject.h"

class GameTimer: public GameObject {
    float timeout;
    float timeLeft;
    bool _started;

public:
    /**
     * Construct a game timer with the given timeout
     */
    explicit GameTimer(float timeout);

    /**
     * Start the timer
     */
    void start() override;

    /**
     * Update the timer
     * @param delta time since last update
     */
    void update(float delta) override;

    /**
     * Set the timer to time out. This also resets the timer
     * @param timeout time to time out
     */
    void setTimeout(float timeout);

    /**
     * Reset the timer
     */
    void reset();

    /**
     * Check if the timer has started
     */
    bool started() const;

    /**
     * get the time on timer Timeleft
     */
    float getTimeLeft() const;

    struct Events {
        constexpr static auto Timeout = "Timeout";
    };
};
