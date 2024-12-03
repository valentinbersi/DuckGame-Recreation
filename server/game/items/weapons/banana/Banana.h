#include "Item.h"

class Banana: public Item {
private:
    bool wasSteped;
    void onCollision();
public:
    Banana(ItemID id, const Vector2 position, const Vector2 direction);

    /**
     * Checks if the banana was stepped. otherwise keeps decreasing the velocity.
     */
    void update(float delta) override;

    ~Banana() override;
};
