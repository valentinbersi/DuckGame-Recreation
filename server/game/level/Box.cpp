#include "Box.h"

#include <memory>
#include <utility>

#include "Explosion.h"
#include "Item.h"
#include "ItemFactory.h"
#include "Layer.h"

#define DIMENSIONS 2, 2
#define ITEM 7
#define EXPLOSION 1
#define GENERATE_OPTIONS 0, 10

Box::Box(Vector2 position):
        PhysicsObject(std::move(position), Layer::Box,
                      Layer::DeathZone | Layer::Bullet | Layer::Player | Layer::Wall | Layer::Box,
                      DIMENSIONS, Gravity::Enabled, Vector2::ZERO, CollisionType::Slide),
        randomGenerator(GENERATE_OPTIONS),
        wasDestroid(false) {}

void Box::eliminateBox() {
    int randomNumber = randomGenerator();
    if (randomNumber <= EXPLOSION) {
        std::unique_ptr<Explosion> explosion = std::make_unique<Explosion>(globalPosition());
        parent()->addChild("Explosion", std::move(explosion));
    } else if (randomNumber <= ITEM) {
        std::unique_ptr<Item> item =
        ItemFactory::createItem(ItemID::randomItemID(), 0, Force::Yes);
        item->setPosition(globalPosition());
        parent()->addChild("Item", std::move(item));
    }
    parent()->removeChild(this);
}

void Box::onCollision() { wasDestroid = true; }

void Box::update([[maybe_unused]]float delta) {
    if(wasDestroid){
        eliminateBox();
    }
}
SizedObjectData Box::status() const { return {position(), DIMENSIONS}; }

Box::~Box() = default;
