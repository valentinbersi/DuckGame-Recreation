
#include "ItemFactory.h"
#include "WeaponSpawn.h"

#define SPAWN_TIME_RANGE 5.0f, 20.0f

#define eventHandler(Function,                                                                   \
                     ...) /*como no se recibe argumentos en este caso quito coma y __VA_ARGS__*/ \
    std::make_unique<gameObject::EventHandler<WeaponSpawn>>(getReference<WeaponSpawn>(), Function)

RandomFloatGenerator WeaponSpawn::randomGenerator(SPAWN_TIME_RANGE);

WeaponSpawn::WeaponSpawn(Vector2 position):
        GameObject2D(nullptr, position), spawnedItem(), timer(new GameTimer(0)) {
    timer->connect("Timeout", eventHandler(&WeaponSpawn::onTimeout));
    addChild("Timer", timer);
}

void WeaponSpawn::onTimeout() {
    std::unique_ptr<Item> item = ItemFactory::createItem(ItemID::randomItemID());
    item->setPosition(position());
    spawnedItem = item->getReference<Item>();
    getRoot()->addChild("Weapon", std::move(item));
    timer->reset();
}

void WeaponSpawn::update([[maybe_unused]] const float delta) {
    if (spawnedItem.expired() && !timer->started()) {
        timer->setTimeout(randomGenerator.generateRandomFloat());
        timer->start();
    }
}

WeaponSpawn::~WeaponSpawn() = default;
