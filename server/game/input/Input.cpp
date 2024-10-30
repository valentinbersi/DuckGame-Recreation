#include "Input.h"

#include <utility>

void Input::setAction(const InputName& action, const bool value) {
    const auto input = inputs.find(action);

    if (input == inputs.end())
        return;

    input->second = value;
}

Input::Input() = default;

void Input::addAction(InputName action) { inputs.insert({std::move(action), false}); }

void Input::removeAction(const InputName& action) { inputs.erase(action); }

void Input::pressAction(const InputName& action) { setAction(action, true); }

void Input::releaseAction(const InputName& action) { setAction(action, false); }

bool Input::isActionPressed(const InputName& action) const { return inputs.find(action)->second; }
