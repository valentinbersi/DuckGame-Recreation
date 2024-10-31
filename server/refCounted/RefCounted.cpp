#include "RefCounted.h"

RefCounted::RefCounted(): refCounter(this, [](RefCounted*) {}) {}

RefCounted::~RefCounted() = default;
