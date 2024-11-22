#include "RandomGenerator.h"


// RandomFloatGenerator definitions

RandomFloatGenerator::RandomFloatGenerator(float min, float max): gen(rd()), dist(min, max) {}

float RandomFloatGenerator::generateRandomFloat() { return dist(gen); }

RandomFloatGenerator::~RandomFloatGenerator() = default;

// RandomIntGenerator definitions

RandomIntGenerator::RandomIntGenerator(int min, int max): gen(rd()), dist(min, max) {}

int RandomIntGenerator::generateRandomInt() { return dist(gen); }

RandomIntGenerator::~RandomIntGenerator() = default;
