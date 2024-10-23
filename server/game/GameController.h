#pragma once

#include "Player.h"
#include "Startable.h"
#include "ThreadSafeHashMap.h"
#include "Updatable.h"

typedef std::uint16_t PlayerID;

class GameController final: public Startable, public Updatable {
    HashMap<PlayerID, Player> players;

public:
    ~GameController() override;

    void start() override;

    void update(float delta) override;

    void updateInternal(float delta) override;
};
