#pragma once
#include "Area.h"
#include "GameTimer.h"
#include "SizedObjectData.h"

class Explosion : public Area {
private:
    GameTimer* timer;

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

    SizedObjectData status() const;

    ~Explosion() override;

};