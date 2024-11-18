#pragma once
#include <cstdint>
#include <string>

#include "GunID.h"
#include "Types.h"

using u8 = std::uint8_t;

/**
 * Relevant data for rendering a gun in the game
 */
struct EquippedGunData {
    GunID gunID;

    EquippedGunData() = delete;
    EquippedGunData(const EquippedGunData& other);
    EquippedGunData& operator=(const EquippedGunData& other);
    EquippedGunData(EquippedGunData&& other) noexcept;
    EquippedGunData& operator=(EquippedGunData&& other) noexcept;

    /**
     * Construct a GunData with the given GunID
     */
    explicit EquippedGunData(GunID gunID);
};
