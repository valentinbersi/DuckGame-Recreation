#pragma once

#include <functional>  // If IDE shows this as unused include, don't remove it, otherwise server won't compile
#include <list>
#include <utility>

#include <bits/ranges_algo.h>

#include "Method.h"

/**
 * A struct for referencing different template instantiation of events
 */
struct EventBase {
    EventBase() = default;
    EventBase(const EventBase& other) = default;
    EventBase& operator=(const EventBase& other) = default;
    EventBase(EventBase&& other) noexcept = default;
    EventBase& operator=(EventBase&& other) noexcept = default;
    virtual ~EventBase() = default;
};

/**
 * An event that will call all connected methods when emitted
 * @tparam Obj The type of the object that the callables are member functions of
 * @tparam Args The types of the arguments to pass to the methods
 */
template <typename Obj, typename... Args>
class Event final: public EventBase {
    std::list<Method<Obj, void, Args...>> methods;

public:
    Event() noexcept = default;
    Event(const Event& other) noexcept;
    Event& operator=(const Event& other) noexcept;
    Event(Event&& other) noexcept;
    Event& operator=(Event&& other) noexcept;
    ~Event() override = default;

    /**
     * Connect a callable to the event
     * @param method The method to connect, this method should not throw exceptions
     */
    void connect(Method<Obj, void, Args...> method) noexcept;

    /**
     * Fire the event. This will call all connected methods with the given arguments.
     * @param args The arguments to pass to the callables
     */
    void fire(Args... args);
};

template <typename Object, typename... Args>
Event<Object, Args...>::Event(const Event& other) noexcept: methods(other.methods) {}

template <typename Object, typename... Args>
Event<Object, Args...>& Event<Object, Args...>::operator=(const Event& other) noexcept {
    if (this == &other)
        return *this;

    methods = other.methods;
    return *this;
}

template <typename Obj, typename... Args>
Event<Obj, Args...>::Event(Event&& other) noexcept: methods(std::move(other.methods)) {}

template <typename Obj, typename... Args>
Event<Obj, Args...>& Event<Obj, Args...>::operator=(Event&& other) noexcept {
    if (this == &other)
        return *this;

    methods = std::move(other.methods);
    return *this;
}

template <typename Obj, typename... Args>
void Event<Obj, Args...>::connect(Method<Obj, void, Args...> method) noexcept {
    methods.push_back(std::move(method));
}

template <typename Obj, typename... Args>
void Event<Obj, Args...>::fire(Args... args) {
    std::ranges::remove_if(methods, [&args...](const Method<Obj, void, Args...>& method) -> bool {
        if (not method.isValid())
            return true;

        method(args...);
        return false;
    });
}
