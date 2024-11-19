#pragma once

struct DuckState {
    bool playingDead;    // cppcheck-suppress unusedStructMember
    bool crouching;      // cppcheck-suppress unusedStructMember
    bool inAir;          // cppcheck-suppress unusedStructMember
    bool flapping;       // cppcheck-suppress unusedStructMember
    bool beingDamaged;   // cppcheck-suppress unusedStructMember
    bool movingRight;    // cppcheck-suppress unusedStructMember
    bool movingLeft;     // cppcheck-suppress unusedStructMember
    bool hasHelmet;      // cppcheck-suppress unusedStructMember
    bool hasChestplate;  // cppcheck-suppress unusedStructMember
    bool isShooting;     // cppcheck-suppress unusedStructMember
};
