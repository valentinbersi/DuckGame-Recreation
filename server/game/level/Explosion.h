#pragma once
#include "Area.h"
#include "GameTimer.h"
#include "SizedObjectData.h"

class Explosion: public Area {
private:
    GameTimer* timer;
    bool hasFinished;
    /**
     * Handlers the collision with the objects, in this case
     * with players or boxes.
     */
    void onCollision(CollisionObject* object);

    /**
     * Eliminates the area fron Level on timer
     * finishes
     */
    void onTimeout();

public:
    /**
     * Creates Explosion Area
     */
    Explosion(const Vector2& position);

    /**
     * Checks if the explosion has finished
     */
    void update(float delta) override;

    /**
     * Get the position of the explosion and its dimensions
     * @return the sizedObjectData of the explosion
     */
    SizedObjectData status() const;

    ~Explosion() override;
};