#include "Box.h"

#include <memory>
#include <utility>

#include "Item.h"
#include "ItemFactory.h"
#include "Layer.h"

#define DIMENSIONS 2, 2
#define ITEM 1
#define EXPLOSION 2
#define GENERATE_OPTIONS 0, 2

Box::Box(Vector2 position):
        PhysicsObject(std::move(position), Layer::Box,
                      Layer::DeathZone | Layer::Bullet | Layer::Player | Layer::Wall | Layer::Box,
                      DIMENSIONS, Gravity::Enabled, Vector2::ZERO, CollisionType::Slide),
        randomGenerator(GENERATE_OPTIONS),
        _wasDestroid(false) {}

void Box::eliminateBox() {
    switch (randomGenerator()) {
        case (ITEM): {
            std::unique_ptr<Item> item =
                    ItemFactory::createItem(ItemID::randomItemID(), 0, Force::Yes);
            item->setPosition(globalPosition());
            parent()->addChild("Item", std::move(item));
            break;
        }
        case EXPLOSION:
            break;

        default:
            break;
    }
    _wasDestroid = true;
}

bool Box::wasDestroyed() const { return _wasDestroid; }

void Box::onCollision() { eliminateBox(); }

SizedObjectData Box::status() const { return {position(), DIMENSIONS}; }

Box::~Box() = default;
