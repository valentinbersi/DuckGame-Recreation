#include "ObjectData.h"

ObjectData::ObjectData(const ObjectData& other) = default;

ObjectData& ObjectData::operator=(const ObjectData& other) = default;

ObjectData::ObjectData(ObjectData&& other) noexcept: _id(other._id) {}

ObjectData& ObjectData::operator=(ObjectData&& other) noexcept {
    _id = other._id;
    return *this;
}

ObjectData::~ObjectData() = default;

ObjectData::ObjectData(const u32 id): _id(id) {}

u32 ObjectData::id() const { return _id; }