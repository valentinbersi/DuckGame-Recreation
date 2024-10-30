#pragma once

#include <forward_list>
#include <functional>

#include <bits/ranges_algo.h>

#include "Types.h"

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
 * An event that will call all connected callables when emitted
 * @tparam Args The types of the arguments to pass to the callables
 */
template <typename... Args>
class Event final: public EventBase {
    std::forward_list<Callable<Args...>> callables;

public:
    Event() noexcept;
    Event(const Event& other) noexcept;
    Event& operator=(const Event& other) noexcept;
    Event(Event&& other) noexcept;
    Event& operator=(Event&& other) noexcept;
    ~Event() override;

    /**
     * Connect a callable to the event
     * @param callable The callable to connect
     */
    void connect(Callable<Args...> callable);

    /**
     * Fire the event. This will call all connected callables with the given arguments
     * @param args The arguments to pass to the callables
     */
    void fire(Args... args);
};

template <typename... Args>
Event<Args...>::Event() noexcept = default;

template <typename... Args>
Event<Args...>::Event(const Event& other) noexcept: callables(other.callables) {}

template <typename... Args>
Event<Args...>& Event<Args...>::operator=(const Event& other) noexcept {
    if (this == &other)
        return *this;

    callables = other.callables;
    return *this;
}

template <typename... Args>
Event<Args...>::Event(Event&& other) noexcept: callables(std::move(other.callables)) {}

template <typename... Args>
Event<Args...>& Event<Args...>::operator=(Event&& other) noexcept {
    if (this == &other)
        return *this;

    callables = std::move(other.callables);
    return *this;
}

template <typename... Args>
Event<Args...>::~Event() = default;

template <typename... Args>
void Event<Args...>::connect(Callable<Args...> callable) {
    callables.push_front(callable);
}

template <typename... Args>
void Event<Args...>::fire(Args... args) {
    std::ranges::for_each(callables,
                          [&args...](Callable<Args...>& callable) { callable(args...); });
}
