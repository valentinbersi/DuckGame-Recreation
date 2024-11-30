#pragma once

#include "Vector2.h"

class GlobalPhysics {
    const float gravityScalar;

    /**
     * Construct a gloabal physics object
     */
    GlobalPhysics();

public:
    GlobalPhysics(const GlobalPhysics& other) = delete;
    GlobalPhysics(GlobalPhysics&& other) noexcept = delete;
    GlobalPhysics& operator=(const GlobalPhysics& other) = delete;
    GlobalPhysics& operator=(GlobalPhysics&& other) noexcept = delete;
    ~GlobalPhysics();

    /**
     * Get the global physics object
     * @return The global physics object
     */
    static GlobalPhysics& get();

    /**
     * Get the gravity vector
     * @return The gravity vector
     */
    Vector2 gravity() const;
};
