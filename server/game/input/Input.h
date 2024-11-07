#pragma once

#include <string>

#include "ThreadSafeHashMap.h"

/**
 * Represents the input of a player
 */
class Input {
    HashMap<std::string, bool> inputs;

public:
    Input() noexcept;
    Input(const Input& other) noexcept;
    Input& operator=(const Input& other) noexcept;
    Input(Input&& other) noexcept;
    Input& operator=(Input&& other) noexcept;

    /**
     * Add a given action to the input
     *  @param action the action to add
     *  @return a reference to the input
     */
    Input& addAction(std::string action);

    /**
     * Remove a given action from the input
     * @param action the action to remove
     * @return a reference to the input
     */
    Input& removeAction(const std::string& action);

    /**
     * Sets the given action as pressed
     * @param action the action to set as pressed
     * @return a reference to the input
     */
    Input& pressAction(const std::string& action);

    /**
     * Sets the given action as not pressed
     * @param action the action to set as not pressed
     * @return a reference to the input
     */
    Input& releaseAction(const std::string& action);

    /**
     * Check whether the given action is pressed
     * @param action the action to check
     * @return true if the given action is pressed, false otherwise
     */
    bool isActionPressed(const std::string& action) const;
};
