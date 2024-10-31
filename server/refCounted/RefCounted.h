#pragma once

#include <memory>

/**
 * An object that keeps tracks of the references to itself
 */
class RefCounted {
    std::shared_ptr<RefCounted> refCounter;

public:
    RefCounted();
    RefCounted(const RefCounted& other) = delete;
    RefCounted& operator=(const RefCounted& other) = delete;
    RefCounted(RefCounted&& other) noexcept = delete;
    RefCounted& operator=(RefCounted&& other) noexcept = delete;
    virtual ~RefCounted();

    /**
     * Get a weak reference to this object
     * @tparam T the type of the pointer, must be a subclass of RefCounted
     * @return a weak reference to this object
     */
    template <typename T>
    [[nodiscard]] std::weak_ptr<T> weakReference() const;

    /**
     * Get a shared reference to this object
     * @tparam T the type of the pointer, must be a subclass of RefCounted
     * @return a shared reference to this object
     */
    template <typename T>
    [[nodiscard]] std::shared_ptr<RefCounted> sharedReference() const;
};

template <typename T>
std::weak_ptr<T> RefCounted::weakReference() const {
    static_assert(std::is_base_of_v<RefCounted, T>);

    return std::static_pointer_cast<T>(refCounter);
}

template <typename T>
std::shared_ptr<RefCounted> RefCounted::sharedReference() const {
    static_assert(std::is_base_of_v<RefCounted, T>);

    return std::static_pointer_cast<T>(refCounter);
}
