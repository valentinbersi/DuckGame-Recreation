#include "DuckData.h"

#define HAS_ARMOR_INDEX 0
#define IS_PLAYING_DEAD_INDEX 1
#define IS_CROUCHING_INDEX 2
#define IS_IN_AIR_INDEX 3
#define IS_FLAPPING_INDEX 4

DuckData::DuckData(const DuckData& other):
        GameObject2DData(other),
        _id(other._id),
        _life(other._life),
        _gun(new GunData(*other._gun)),
        _actions(other._actions) {}

DuckData& DuckData::operator=(const DuckData& other) {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(other);
    _id = other._id;
    _life = other._life;
    _gun = new GunData(*other._gun);
    _actions = other._actions;
    return *this;
}

DuckData::DuckData(DuckData&& other) noexcept:
        GameObject2DData(std::move(other)),
        _id(other._id),
        _life(other._life),
        _gun(other._gun),
        _actions(other._actions) {
    other._gun = nullptr;
}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    _id = other._id;
    _life = other._life;
    _gun = other._gun;
    other._gun = nullptr;
    _actions = other._actions;
    return *this;
}

DuckData::~DuckData() { delete _gun; }

DuckData::DuckData(const GameObjectID objectID, Vector2 position, const f32 rotation,
                   const DuckID duckID, const u8 life, std::unique_ptr<GunData> gun,
                   const DuckActions actions):
        GameObject2DData(objectID, std::move(position), rotation),
        _id(duckID),
        _life(life),
        _gun(gun.release()),
        _actions(actions) {}

DuckID DuckData::duckID() const { return _id; }

u8 DuckData::life() const { return _life; }

const GunData& DuckData::gun() const { return *_gun; }

bool DuckData::hasArmor() const { return _actions.test(HAS_ARMOR_INDEX); }

bool DuckData::isPlayingDead() const { return _actions.test(IS_PLAYING_DEAD_INDEX); }

bool DuckData::isCrouching() const { return _actions.test(IS_CROUCHING_INDEX); }

bool DuckData::isInAir() const { return _actions.test(IS_IN_AIR_INDEX); }

bool DuckData::isFlapping() const { return _actions.test(IS_FLAPPING_INDEX); }
