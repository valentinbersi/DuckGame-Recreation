
#include "ItemSpawner.h"

#include <utility>

#include "ItemFactory.h"

#define SPAWN_TIME_RANGE 5.0f, 20.0f
#define SPAWNER_DIMENSIONS 2, 2

#define eventHandler(Function)  /*como no se recibe argumentos en este caso quito coma y __VA_ARGS__*/ \
   gameObject::EventHandler<ItemSpawner>::create(getReference<ItemSpawner>(), Function)

RandomFloatGenerator ItemSpawner::randomGenerator(SPAWN_TIME_RANGE);

ItemSpawner::ItemSpawner(Vector2 position):
        GameObject2D(nullptr, position), spawnedItem(), timer(new GameTimer(0)) {
    timer->connect("Timeout", eventHandler(&ItemSpawner::onTimeout));
    addChild("Timer", timer);
}

void ItemSpawner::onTimeout() {
    std::unique_ptr<Item> item = ItemFactory::createItem(ItemID::randomItemID());
    item->setPosition(position());
    spawnedItem = item->getReference<Item>();
    getRoot()->addChild("Weapon", std::move(item));
    timer->reset();
}

void ItemSpawner::update([[maybe_unused]] const float delta) {
    if (spawnedItem.expired() && !timer->started()) {
        timer->setTimeout(randomGenerator.generateRandomFloat());
        timer->start();
    }
}

SizedObjectData ItemSpawner::status() const {
    return {position(), SPAWNER_DIMENSIONS};
}

ItemSpawner::~ItemSpawner() = default;
