#pragma once

#include "ThreadSafeHashMap.h"

typedef std::string InputName;

/**
 * Represents the input of a player
 */
class Input {
    ThreadSafeMap<InputName, bool> inputs;

public:
    /**
     * Creates a new input
     */
    Input();

    /**
     * Add a given action to the input
     *  @param action the action to add
     */
    void addAction(const InputName& action);

    /**
     * Remove a given action from the input
     * @param action the action to remove
     */
    void removeAction(const InputName& action);

    /**
     * Sets the given action as pressed
     * @param action the action to set as pressed
     */
    void pressAction(const InputName& action);

    /**
     * Sets the given action as not pressed
     * @param action the action to set as not pressed
     */
    void releaseAction(const InputName& action);

    /**
     * Check whether the given action is pressed
     * @param action the action to check
     * @return true if the given action is pressed, false otherwise
     */
    bool isActionPressed(const InputName& action);
};
