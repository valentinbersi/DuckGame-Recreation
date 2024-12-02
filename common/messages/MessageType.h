#pragma once
#include <functional>
class MessageType {
public:
    enum Value : unsigned char { Lobby = 0x0, Game = 0x1, Reply = 0x2 };

    // cppcheck-suppress noExplicitConstructor
    MessageType(Value value);  // NOLINT(runtime/explicit)

    // cppcheck-suppress noExplicitConstructor
    MessageType(unsigned char value);  // NOLINT(runtime/explicit)

    [[nodiscard]] operator Value() const;

    MessageType() = delete;

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
        ACTION_RELEASED = 0xB,
        SHOOT_PRESSED = 0xC,
        SHOOT_RELEASED = 0xD,
        NEXT_ROUND = 0xE,
        END_ROUND_CHEAT = 0xF,
        END_GAME_CHEAT = 0x10,
        WEAPON_CHEAT = 0x11, //auxiliar
        AK47_CHEAT = 0x12,
        SHOTGUN_CHEAT = 0x13,
        MAGNUM_CHEAT = 0x14,
        COWBOYPISTOL_CHEAT = 0x15,
        DUELPISTOL_CHEAT = 0x16,
        SNIPER_CHEAT = 0x17,
        LASER_RIFLE_CHEAT = 0x18,
        PEWPEW_CHEAT = 0x19,
        GRENADE_CHEAT = 0x1A,
        BANANA_CHEAT = 0x1B,
        ARMOR_CHEAT = 0x1C,
        HELMET_CHEAT = 0x1D,
        INFINITE_AMMO = 0x1E
    };

    // cppcheck-suppress noExplicitConstructor
    InputAction(Value value);  // NOLINT(runtime/explicit)

    // cppcheck-suppress noExplicitConstructor
    InputAction(unsigned char value);  // NOLINT(runtime/explicit)

    [[nodiscard]] operator Value() const;

    InputAction() = delete;

private:
    Value _value;

    friend struct std::hash<InputAction>;

    friend struct std::equal_to<InputAction>;
};

template <>
struct std::hash<InputAction> {
    std::size_t operator()(const InputAction& InputAction) const {
        return std::hash<InputAction::Value>()(InputAction._value);
    }
};

template <>
struct std::equal_to<InputAction> {
    bool operator()(const InputAction& firstID, const InputAction& secondID) const {
        return firstID._value == secondID._value;
    }
};


class LobbyRequest {
public:
    enum Value : unsigned char {
        NEWMATCH = 0x0,
        JOINMATCH = 0x1,
        CHOOSECOLOR = 0X2,
        STARTMATCH = 0X3
    };

    // cppcheck-suppress noExplicitConstructor
    LobbyRequest(Value value);  // NOLINT(runtime/explicit)

    // cppcheck-suppress noExplicitConstructor
    LobbyRequest(unsigned char value);  // NOLINT(runtime/explicit)

    [[nodiscard]] operator Value() const;

    LobbyRequest() = delete;

private:
    Value _value;
};
