#include "Box.h"
#include "Layer.h"
#include "Item.h"
#include "ItemFactory.h"

#define DIMENSIONS 2,2
#define ITEM 1
#define EXPLOSION 2
#define GENERATE_OPTIONS 0, 2

Box::Box(Vector2 position): 
    PhysicsObject(std::move(position), Layer::Box, Layer::DeathZone | Layer::Bullet | Layer::Player |
                  Layer::Wall, DIMENSIONS, Gravity::Enabled, Vector2::ZERO ,CollisionType::Bounce),
    randomGenerator(GENERATE_OPTIONS) {}

void Box::eliminateBox() {
    switch(randomGenerator()){
        case (ITEM) :
        {
            std::unique_ptr<Item> item = ItemFactory::createItem(ItemID::randomItemID());
            item->setPosition(globalPosition());
            parent()->addChild("Item", std::move(item));
            break;
        }
        case EXPLOSION:
            break;
        default:
            break;    
    }
    parent()->removeChild(this);
}

void Box::onCollision(const CollisionObject* object) {
    if (object->layers().test(Layer::Bullet)) {
        return eliminateBox();
    }
}

SizedObjectData Box::status() const { return {position(), DIMENSIONS}; }

Box::~Box() = default;
