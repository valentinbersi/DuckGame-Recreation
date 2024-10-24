#pragma once

#include <bitset>

#include "EquippedGunData.h"
#include "GameObject2DData.h"

enum class DuckID : u8 {
    RED = 0x1
};

typedef u8 DuckActions;

/**
 * Relevant data for rendering a duck
 */
class DuckData final: public GameObject2DData {
    constexpr static u8 NFLAGS = 5;

    DuckID _id;
    u8 _life;
    EquippedGunData* _gun;
    std::bitset<NFLAGS> _actions;

protected:
    std::string _data() override;

public:
    DuckData() = delete;
    DuckData(const DuckData& other);
    DuckData& operator=(const DuckData& other);
    DuckData(DuckData&& other) noexcept;
    DuckData& operator=(DuckData&& other) noexcept;
    ~DuckData() override;

    constexpr static DuckActions HAS_ARMOR = 0b1;
    constexpr static DuckActions IS_PLAYING_DEAD = 0b01;
    constexpr static DuckActions IS_CROUCHING = 0b001;
    constexpr static DuckActions IS_IN_AIR = 0b0001;
    constexpr static DuckActions IS_FLAPPING = 0b00001;

    /**
     * Construct a DuckData object
     * @param position the object's position
     * @param rotation the object's rotation
     * @param duckID the duck's ID
     * @param life the life of the duck
     * @param gun the gun of the duck
     * @param actions the actions the duck is performing
     */
    DuckData(Vector2 position, f32 rotation, DuckID duckID, u8 life,
             std::unique_ptr<EquippedGunData> gun, DuckActions actions);

    /**
     * Get the duckID of the duck
     * @return the duckID of the duck
     */
    [[nodiscard]] DuckID duckID() const;

    /**
     * Get the life of the duck
     * @return the life of the duck
     */
    [[nodiscard]] u8 life() const;

    /**
     * Get the gun of the duck \n
     * WARNING: this is a reference to dynamic data, so once the DuckData is deleted, this reference
     * will be invalid.
     * @return the gun of the duck
     */
    [[nodiscard]] const EquippedGunData& gun() const;

    /**
     * Check if the duck has armor
     * @return true if the duck has armor, false otherwise
     */
    [[nodiscard]] bool hasArmor() const;

    /**
     * Check if the duck is playing dead
     * @return true if the duck is playing dead, false otherwise
     */
    [[nodiscard]] bool isPlayingDead() const;

    /**
     * Check if the duck is crouching
     * @return true if the duck is crouching, false otherwise
     */
    [[nodiscard]] bool isCrouching() const;

    /**
     * Check if the duck is in the air
     * @return true if the duck is in the air, false otherwise
     */
    [[nodiscard]] bool isInAir() const;

    /**
     * Check if the duck is flapping
     * @return true if the duck is flapping, false otherwise
     */
    [[nodiscard]] bool isFlapping() const;
};
