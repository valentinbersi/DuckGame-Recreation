#include "TrackedReference.h"

TrackedReference::TrackedReference(): refCounter(this, [](TrackedReference*) {}) {}

TrackedReference::~TrackedReference() = default;
