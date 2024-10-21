#pragma once

class MessageType {
public:
    enum Value : unsigned char { Input = 0x0, NewMatch = 0x1, JoinMatch = 0x2, StartMatch = 0x3};

    // cppcheck-suppress noExplicitConstructor
    MessageType(Value value) : _value(value) {} // Implicit on purpose so it can be used as a common enum

    [[nodiscard]] operator Value() const {return _value;}

    MessageType() = delete;

    // bool operator==(MessageType boxId) const;

    // bool operator!=(MessageType boxId) const;

private:
    Value _value;
};

class InputAction {
public:
    enum Value : unsigned char { LEFT = 0x0, RIGHT = 0x1};

    // cppcheck-suppress noExplicitConstructor
    InputAction(Value value) : _value(value) {} // Implicit on purpose so it can be used as a common enum

    [[nodiscard]] operator Value() const {return _value;}

    InputAction() = delete;

    // bool operator==(InputAction boxId) const;

    // bool operator!=(InputAction boxId) const;

private:
    Value _value;
};
