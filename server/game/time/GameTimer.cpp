#include "GameTimer.h"

GameTimer::GameTimer(const float timeout): timeout(timeout), timeLeft(timeout), _started(false) {
    registerEvent(Events::Timeout);
}

void GameTimer::start() { _started = true; }

void GameTimer::update(const float delta) {
    if (!_started)
        return;

    timeLeft -= delta;

    if (timeLeft <= 0) {
        _started = false;
        fire(Events::Timeout);
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

float GameTimer::getTimeLeft() const { return timeLeft; }
