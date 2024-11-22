#include "GameTimer.h"

GameTimer::GameTimer(const float timeout):
        GameObject(nullptr), timeout(timeout), timeLeft(timeout), _started(false) {
    registerEvent("Timeout");
}

void GameTimer::start() { _started = true; }

void GameTimer::update(const float delta) {
    if (!_started)
        return;

    timeLeft -= delta;
    if (timeout - timeLeft <= 0) {
        _started = false;
        fire("Timeout");
    }
}

void GameTimer::setTimeout(const float timeout) {
    this->timeout = timeout;
    reset();
}

void GameTimer::reset() {
    timeLeft = timeout;
    _started = false;
}

bool GameTimer::started() const { return _started; }
