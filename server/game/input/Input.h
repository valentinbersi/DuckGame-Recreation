#pragma once

#include <string>
#include <utility>

#include "Types.h"

/**
 * Represents the input of a player
 */
class Input {
    HashMap<std::string, std::pair<bool, bool>> inputs;

public:
    /**
     * An exception thrown when trying to add an action that's already been added
     */
    struct AlreadyAddedAction final: std::runtime_error {
        /**
         * Construct an AlreadyAddedAction with the given action names
         */
        explicit AlreadyAddedAction(const std::string& actionName);
    };

    /**
     * An exception thrown when trying to remove an action that wasn't added
     */
    struct ActionNotFound final: std::runtime_error {
        /**
         * Construct an ActionNotAdded with the given action names
         */
        explicit ActionNotFound(const std::string& actionName);
    };

    Input() noexcept;
    Input(const Input& other) noexcept;
    Input& operator=(const Input& other) noexcept;
    Input(Input&& other) noexcept;
    Input& operator=(Input&& other) noexcept;

    /**
     * Add a given action to the input
     *  @param action the action to add
     *  @return a reference to the input
     *  @throws AlreadyAddedAction if the action was already added to the input
     */
    Input& addAction(std::string action);

    /**
     * Remove a given action from the input
     * @param action the action to remove
     * @return a reference to the input
     * @throws ActionNotFound if the action was not found
     */
    Input& removeAction(const std::string& action);

    /**
     * Sets the given action as pressed
     * @param action the action to set as pressed
     * @return a reference to the input
     * @throws std::out_of_range if the action is not found
     */
    Input& pressAction(const std::string& action);

    /**
     * Sets the given action as not pressed
     * @param action the action to set as not pressed
     * @return a reference to the input
     * @throws std::out_of_range if the action is not found
     */
    Input& releaseAction(const std::string& action);

    /**
     * Check whether the given action is pressed
     * @param action the action to check
     * @return true if the given action is pressed, false otherwise
     * @throws std::out_of_range is the action is not found
     */
    bool isActionPressed(const std::string& action) const;

    /**
     * Checks if a given action is just pressed
     * @param action the action to check
     * @return true if the given action is just pressed, false otherwise
     * @throws std::out_of_range is the action is not found
     */
    bool isActionJustPressed(const std::string& action) const;

    /**
     * Resets the inputs that are just pressed.
     */
    void reset();
};
