#pragma once

#include "Types.h"

struct Layer {
    enum Value : u8 { Player = 0b1, Wall = 0b10, Item = 0b100, Spawner = 0b1000 };

    struct Index {
        enum Value : u8 {
            Player = 0,
            Wall = 1,
            Item = 2,
            Spawner = 3,
        };
    };

    Layer() = delete;
    Layer(const Layer& other) = delete;
    Layer(Layer&& other) noexcept = delete;
    Layer& operator=(const Layer& other) = delete;
    Layer& operator=(Layer&& other) noexcept = delete;
    ~Layer() = delete;
};
