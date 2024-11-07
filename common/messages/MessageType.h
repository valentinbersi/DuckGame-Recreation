#pragma once

class MessageType {
public:
    enum Value : unsigned char { Lobby = 0x0, Game = 0x1, Reply = 0x2 };

    // cppcheck-suppress noExplicitConstructor
    MessageType(Value value):
            _value(value) {}  // Implicit on purpose so it can be used as a common enum

    // cppcheck-suppress noExplicitConstructor
    MessageType(unsigned char value):
            _value(static_cast<Value>(value)) {
    }  // Implicit on purpose so it can be used as a common enum


    [[nodiscard]] operator Value() const { return _value; }

    MessageType() = delete;

    // bool operator==(const MessageType& other) const {return _value == other._value;}

    // bool operator!=(MessageType boxId) const;

private:
    Value _value;
};

class InputAction {
public:
    enum Value : unsigned char {
        LEFT_PRESSED = 0x0,
        RIGHT_PRESSED = 0x1,
        UP_PRESSED = 0x2,
        DOWN_PRESSED = 0x3,
        JUMP_PRESSED = 0x4,
        ACTION_PRESSED = 0x5,
        LEFT_RELEASED = 0x6,
        RIGHT_RELEASED = 0x7,
        UP_RELEASED = 0x8,
        DOWN_RELEASED = 0x9,
        JUMP_RELEASED = 0xA,
        ACTION_RELEASED = 0xB
    };

    // cppcheck-suppress noExplicitConstructor
    InputAction(Value value):
            _value(value) {}  // Implicit on purpose so it can be used as a common enum

    // cppcheck-suppress noExplicitConstructor
    InputAction(unsigned char value): _value(static_cast<Value>(value)) {}

    [[nodiscard]] operator Value() const { return _value; }

    InputAction() = delete;

    // bool operator==(const InputAction& other) const {return _value == other._value;}

    // bool operator!=(InputAction boxId) const;

private:
    Value _value;
};

class LobbyRequest {
public:
    enum Value : unsigned char { NEWMATCH = 0x0, JOINMATCH = 0x1, STARTMATCH = 0X2 };

    // cppcheck-suppress noExplicitConstructor
    LobbyRequest(Value value):
            _value(value) {}  // Implicit on purpose so it can be used as a common enum

    // cppcheck-suppress noExplicitConstructor
    LobbyRequest(unsigned char value): _value(static_cast<Value>(value)) {}

    [[nodiscard]] operator Value() const { return _value; }

    LobbyRequest(): _value(NEWMATCH){};

    // bool operator==(const LobbyRequest& other) const {return _value == other._value;}

    // bool operator!=(LobbyRequest boxId) const;

private:
    Value _value;
};
