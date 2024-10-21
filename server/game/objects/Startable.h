#pragma once

/**
 * An interface for classes that can be started. Useful for objects that need to be initialized
 * after construction.
 */
struct Startable {
    virtual ~Startable() = default;

    /**
     * Start the object.
     */
    virtual void start() = 0;
};
