#pragma once

/**
 * An interface for classes that constantly change state.
 */
struct Updatable {
    virtual ~Updatable() = default;

    /**
     * Update the object.
     * @param delta The time since the last update.
     */
    virtual void update(float delta) = 0;

    /**
     * Update the object with actions that must be performed anyway regarding @code update()@endcode
     * being overridden. Generally, when overriding this method, you'd like to also call the base
     * class one. So every object's attribute is update correctly.
     */
    virtual void updateInternal(float delta) = 0;
};
