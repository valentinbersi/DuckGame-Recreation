#pragma once

/**
 * An interface for classes that can be finished. Useful for objects that need to perform actions
 * prior to being destroyed.
 */
struct Finishable {
    virtual ~Finishable() = default;

    /**
     * Start the object.
     */
    virtual void finish() = 0;

    /**
     * Start the object internally.
     */
    virtual void finishInternal() = 0;
};
