#pragma once
#include <random>

class RandomFloatGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

public:
    /**
     * Constructor for RandomFloatGenerator {
     * @param min The minimum value for the random float
     * @param max The maximum value for the random float
     */
    RandomFloatGenerator(float min, float max);

    /**
     * Generates random values between the given range on construction
     * @return the random float generated
     */
    float generateRandomFloat();

    /**
     * Generates random values between the given range on construction
     * @return the random float generated
     */
    float operator()();

    /**
     * Destructor for RandomFloatGenerator {
     */
    ~RandomFloatGenerator();
};

class RandomIntGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    /**
     * Constructor for RandomIntGenerator {
     * @param min The minimum value for the random int
     * @param max The maximum value for the random int
     */
    RandomIntGenerator(int min, int max);

    /**
     * Generates random values between the given range on construction
     * @return the random int generated
     */
    int generateRandomInt();

    /**
     * Generates random values between the given range on construction
     * @return the random int generated
     */
    int operator()();

    /**
     * Destructor for RandomIntGenerator
     */
    ~RandomIntGenerator();
};
