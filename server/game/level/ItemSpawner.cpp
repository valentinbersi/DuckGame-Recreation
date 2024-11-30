#include "ItemSpawner.h"

#include <utility>

#include "Config.h"
#include "GameController.h"
#include "ItemFactory.h"
#include "Layer.h"

#define SPAWNER_DIMENSIONS 3.5f, 1.5f

#define eventHandler(                                                                    \
        Function) /*como no se recibe argumentos en este caso quito coma y __VA_ARGS__*/ \
    gameObject::EventHandler<ItemSpawner>::create(getReference<ItemSpawner>(), Function)

ItemSpawner::ItemSpawner(Vector2 position):
        StaticObject(std::move(position), Layer::Spawner, 0, SPAWNER_DIMENSIONS),
        timer(new GameTimer(0)),
        randomGenerator(Config::Weapons::minSpawnTime(), Config::Weapons::maxSpawnTime()) {
    timer->connect(GameTimer::Events::Timeout, eventHandler(&ItemSpawner::onTimeout));
    addChild("Timer", timer);
}

void ItemSpawner::onTimeout() {
    std::unique_ptr<Item> item = ItemFactory::createItem(ItemID::randomItemID());

    const float itemHalfHeight = item->getShape().size().y() / 2;
    const float spawnerHalfHeight = getShape().size().y() / 2;

    const Vector2 newPosition = position() + Vector2::UP * (itemHalfHeight + spawnerHalfHeight);
    item->setPosition(newPosition);
    spawnedItem = item->getReference<Item>();
    getRoot<GameController>()->addToLevel("Item", std::move(item));
    timer->setTimeout(randomGenerator.generateRandomFloat());
}

void ItemSpawner::update([[maybe_unused]] const float delta) {
    if (spawnedItem.expired() && !timer->started()) {
        timer->start();
    }
}

SizedObjectData ItemSpawner::status() const { return {position(), SPAWNER_DIMENSIONS}; }

ItemSpawner::~ItemSpawner() = default;
