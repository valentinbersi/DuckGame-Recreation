#include "Input.h"

#include <utility>

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

void Input::addAction(std::string action) { inputs.emplace(std::move(action), false); }

void Input::removeAction(const std::string& action) { inputs.erase(action); }

void Input::pressAction(const std::string& action) { inputs.at(action) = true; }

void Input::releaseAction(const std::string& action) { inputs.at(action) = false; }

bool Input::isActionPressed(const std::string& action) const { return inputs.at(action); }
