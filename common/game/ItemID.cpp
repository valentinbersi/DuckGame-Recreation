#include "ItemID.h"
#include <random>

ItemID::ItemID(Value value): _value(value) {}

ItemID::ItemID(unsigned char value): _value(static_cast<Value>(value)) {}

ItemID::operator Value() const { return _value; }

ItemID ItemID::randomItemID() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<Value> dist(Grenade, Armor);
    return dist(gen);
}
