#pragma once

#include <functional>

/**
 * A wrapper for a class method to make it easier to use std::function with them. The given object
 * must be valid at the time of the call. The object is not owned by the Method object, so it won't
 * free it when it's destroyed.
 */
template <typename Object, typename Ret, typename... Args>
class Method {
    Object* object;
    std::function<Ret(Object*, Args...)> method;

public:
    Method() = delete;
    Method(const Method& other) noexcept;
    Method& operator=(const Method& other) = delete;
    Method(Method&& other) noexcept;
    Method& operator=(Method&& other) noexcept = delete;

    /**
     * Construct a Method wrapper for the given object and method
     * @param object The object to call the method on
     * @param method The method to call
     * @throw std::invalid_argument if the given object is null
     */
    explicit Method(Object* object, std::function<Ret(Object*, Args...)> method);

    /**
     * Call the method on the object. The object given at the construction must still be valid
     * @param args The arguments to pass to the method
     * @throw std::runtime_error if the inner object is null (probably moved)
     */
    Ret operator()(Args... args) const;
};

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(const Method& other) noexcept:
        object(other.object), method(other.method) {}

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(Method&& other) noexcept:
        object(other.object), method(std::move(other.method)) {
    other.object = nullptr;
}

#define NULL_OBJECT "object is nullptr"

template <typename Object, typename Ret, typename... Args>
Method<Object, Ret, Args...>::Method(Object* object, std::function<Ret(Object*, Args...)> method):
        object(object), method(std::move(method)) {
    if (this->object == nullptr)
        throw std::invalid_argument(NULL_OBJECT);
}

#define INVALID_CALL \
    "Method called on nullptr object. Probably you are trying to call a method on a moved object."

template <typename Object, typename Ret, typename... Args>
Ret Method<Object, Ret, Args...>::operator()(Args... args) const {
    if (object == nullptr)
        throw std::runtime_error(INVALID_CALL);

    return method(object, args...);
}
