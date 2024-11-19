#include "GameTimer.h"

GameTimer::GameTimer(const float timeout):
        GameObject(nullptr), timeout(timeout), timeLeft(timeout), started(false) {
    registerEvent("Timeout");
}

void GameTimer::start() { started = true; }

void GameTimer::update(const float delta) {
    if (!started)
        return;

    timeLeft -= delta;
    if (timeout - timeLeft <= 0) {
        started = false;
        fire("Timeout");
    }
}

void GameTimer::setTimeout(const float timeout) {
    this->timeout = timeout;
    reset();
}

void GameTimer::reset() {
    timeLeft = timeout;
    started = false;
}

GameStatus GameTimer::status() { return {}; }