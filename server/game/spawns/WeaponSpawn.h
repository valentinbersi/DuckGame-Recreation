#include "GameObject2D.h"
#include "GameTimer.h"
#include "Item.h"
#include "RandomGenerator.h"
#include <memory>

class WeaponSpawn : public GameObject2D {
private:
    std::weak_ptr<Item> spawnedItem;

    GameTimer* timer;

    static RandomFloatGenerator randomGenerator;

    void onTimeout();

public:

    WeaponSpawn(Vector2 position);

    void update(float delta) override;

    ~WeaponSpawn() override;
};
