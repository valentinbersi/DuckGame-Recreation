#pragma once
#include <memory>

#include "GameObject2D.h"
#include "GameTimer.h"
#include "Item.h"
#include "RandomGenerator.h"
#include "SizedObjectData.h"

class ItemSpawner: public GameObject2D {
private:
    std::weak_ptr<Item> spawnedItem;

    GameTimer* timer;

    static RandomFloatGenerator randomGenerator;

    /**
     * function used on eventHandler in order to
     * spawn a new item
     */
    void onTimeout();

public:
    /**
     * Construct a ItemSpawner with the given position
     * @param position the Vectore representing the spawner position
     */
    explicit ItemSpawner(Vector2 position);

    /**
     * Internally checks is the weapons has been picked up,
     * if so, a timer will be started to spawn a new item
     */
    void update(float delta) override;

    /**
     * Get the positions of the item spawner
     */
    SizedObjectData status() const;

    /**
     * Destroy the ItemSpawner (default)
     */
    ~ItemSpawner() override;
};
