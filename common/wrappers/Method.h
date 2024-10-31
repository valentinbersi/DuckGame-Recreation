#pragma once

#include <functional>
#include <memory>

/**
 * Thrown when trying to call a method on an invalid object
 */
struct InvalidObject final: std::runtime_error {
    InvalidObject();
};

/**
 * A wrapper for a class method
 */
template <typename Object, typename Ret, typename... Args>
class Method {
    constexpr static auto INVALID_OBJECT =
            "The method was called over an object that no longer exists";

    constexpr static auto INVALID_CALL = "Method called on nullptr object. Probably you are trying "
                                         "to call a method on a moved object.";

    constexpr static auto NULL_OBJECT = "object is nullptr";

    std::weak_ptr<Object> object;
    std::function<Ret(Object*, Args...)> method;

public:
    Method() = delete;
    Method(const Method& other) noexcept;
    Method& operator=(const Method& other) noexcept;
    Method(Method&& other) noexcept;
    Method& operator=(Method&& other) noexcept;

    /**
     * Construct a Method wrapper for the given object and method
     * @param object The object to call the method on
     * @param method The method to call
     * @throw std::invalid_argument if the given object is null
     */
    Method(std::weak_ptr<Object> object, std::function<Ret(Object*, Args...)> method);

    /**
     * Call the method on the object. The object given at the construction must still be valid
     * @param args The arguments to pass to the method
     * @throw std::runtime_error if the inner object is null (probably moved)
     */
    Ret operator()(Args... args) const;

    /**
     * Check if the object used to instantiate this method is still valid
     * @return true if the object used to instantiate this method is still valid
     */
    [[nodiscard]] bool isValid() const;
};

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(const Method& other) noexcept:
        object(other.object), method(other.method) {}

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>& Method<Object, Ret, Args...>::operator=(
        const Method& other) noexcept {
    if (this == &other)
        return *this;

    object = other.object;
    method = other.method;
    return *this;
}

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(Method&& other) noexcept:
        object(std::move(other.object)), method(std::move(other.method)) {}

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>& Method<Object, Ret, Args...>::operator=(Method&& other) noexcept {
    if (this == &other)
        return *this;

    object = std::move(other.object);
    method = std::move(other.method);
    return *this;
}

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(std::weak_ptr<Object> object,
                                     std::function<Ret(Object*, Args...)> method):
        object(std::move(object)), method(std::move(method)) {
    if (this->object.lock().get() == nullptr)
        throw std::invalid_argument(NULL_OBJECT);
}

template <typename Object, typename Ret, typename... Args>
Ret Method<Object, Ret, Args...>::operator()(Args... args) const {
    if (object.expired())
        throw std::runtime_error(INVALID_OBJECT);

    if (object.lock().get() == nullptr)
        throw std::runtime_error(INVALID_CALL);

    return method(object.lock().get(), args...);
}

template <typename Object, typename Ret, typename... Args>
bool Method<Object, Ret, Args...>::isValid() const {
    return !object.expired();
}
