#include "Input.h"

#include <utility>

#define ACTION "Action "
#define ALREADY_ADDED " has already been added"

Input::AlreadyAddedAction::AlreadyAddedAction(const std::string& actionName):
        std::runtime_error(ACTION + actionName + ALREADY_ADDED) {}

#define NOT_FOUND " has not been found"

Input::ActionNotFound::ActionNotFound(const std::string& actionName):
        std::runtime_error(ACTION + actionName + NOT_FOUND) {}

Input::Input() noexcept = default;

Input::Input(const Input& other) noexcept = default;

Input& Input::operator=(const Input& other) noexcept {
    if (this == &other)
        return *this;

    inputs = other.inputs;
    return *this;
}

Input::Input(Input&& other) noexcept: inputs(std::move(other.inputs)) {}

Input& Input::operator=(Input&& other) noexcept {
    if (this == &other)
        return *this;

    inputs = std::move(other.inputs);
    return *this;
}

Input& Input::addAction(std::string action) {
    if (inputs.contains(action))
        throw AlreadyAddedAction(action);

    inputs.emplace(std::move(action), std::make_pair(false, false));
    return *this;
}

Input& Input::removeAction(const std::string& action) {
    if (inputs.erase(action) == 0)
        throw ActionNotFound(action);

    return *this;
}

Input& Input::pressAction(const std::string& action) {
    inputs.at(action).first = true;
    inputs.at(action).second = true;
    return *this;
}

Input& Input::releaseAction(const std::string& action) {
    inputs.at(action).first = false;
    inputs.at(action).second = false;
    return *this;
}

bool Input::isActionPressed(const std::string& action) const { 
    return inputs.at(action).first;
}

bool Input::isActionJustPressed(const std::string& action) const{
    return inputs.at(action).second;
}

void Input::reset(){
    for (auto& [_, value] : inputs) {
        value.second = false;
    }
}
