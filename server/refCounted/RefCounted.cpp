#include "RefCounted.h"

RefCounted::RefCounted(): refCounter(this, [](RefCounted*) {}) {}

RefCounted::RefCounted(RefCounted&& other) noexcept: refCounter(std::move(other.refCounter)) {}

RefCounted& RefCounted::operator=(RefCounted&& other) noexcept {
    if (this == &other)
        return *this;

    refCounter = std::move(other.refCounter);
    return *this;
}

RefCounted::~RefCounted() = default;
