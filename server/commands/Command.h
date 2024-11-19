#pragma once
#include "GameController.h"

class Command {
protected:
    const PlayerID id;

public:
    explicit Command(PlayerID id): id(id) {}
    virtual void execute(GameController&) = 0;
    virtual ~Command() = default;
};
