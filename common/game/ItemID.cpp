#include "ItemID.h"

#include <random>

ItemID::ItemID(Value value): _value(value) {}

ItemID::ItemID(unsigned char value): _value(static_cast<Value>(value)) {}

ItemID::operator Value() const { return _value; }

RandomIntGenerator ItemID::randomGenerator(DuelPistol, Sniper);

ItemID ItemID::randomItemID() { return randomGenerator.generateRandomInt(); }
