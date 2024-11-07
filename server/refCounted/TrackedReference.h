#pragma once

#include <memory>

/**
 * A class that allow other objects to track the lifetime of this object
 */
class TrackedReference {
    std::shared_ptr<TrackedReference> refCounter;

protected:
    TrackedReference();
    virtual ~TrackedReference();

public:
    TrackedReference(const TrackedReference& other) = delete;
    TrackedReference& operator=(const TrackedReference& other) = delete;
    TrackedReference(TrackedReference&& other) noexcept = delete;
    TrackedReference& operator=(TrackedReference&& other) noexcept = delete;

    /**
     * Get a reference to this object to track its lifetime
     * @tparam T the type of the pointer, must be a subclass of RefCounted
     * @return a weak reference to this object
     */
    template <typename T>
    [[nodiscard]] std::weak_ptr<T> getReference() const;
};

template <typename T>
std::weak_ptr<T> TrackedReference::getReference() const {
    static_assert(std::is_base_of_v<TrackedReference, T>);
    return std::static_pointer_cast<T>(refCounter);
}
