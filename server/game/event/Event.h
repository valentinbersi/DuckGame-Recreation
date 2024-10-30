#pragma once

#include <forward_list>
#include <functional>
#include <utility>

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

    /**
     * Disconnect a callable from the event
     * @param id The id of the callable
     */
    virtual void disconnect(const std::string& id) = 0;
};

/**
 * An event that will call all connected callables when emitted
 * @tparam Args The types of the arguments to pass to the callables
 */
template <typename... Args>
class Event final: public EventBase {
    HashMap<std::string, Callable<Args...>> callables;

public:
    /**
     * Thrown when trying to connect a callable with an id that is already connected
     */
    struct AlreadyConnectedCallable final: std::runtime_error {
        explicit AlreadyConnectedCallable(const std::string& id);
    };

    Event() noexcept;
    Event(const Event& other) noexcept;
    Event& operator=(const Event& other) noexcept;
    Event(Event&& other) noexcept;
    Event& operator=(Event&& other) noexcept;
    ~Event() override = default;

    /**
     * Connect a callable to the event
     * @param name The id of the callable
     * @param callable The callable to connect
     */
    void connect(std::string name, Callable<Args...> callable);

    /**
     * Disconnect a callable from the event
     * @param id The id of the callable
     */
    void disconnect(const std::string& id) override;

    /**
     * Fire the event. This will call all connected callables with the given arguments
     * @param args The arguments to pass to the callables
     */
    void fire(Args... args);
};

template <typename... Args>
Event<Args...>::AlreadyConnectedCallable::AlreadyConnectedCallable(const std::string& id):
        std::runtime_error("Callable with id " + id + " already connected") {}

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
void Event<Args...>::connect(std::string name, Callable<Args...> callable) {
    if (callables.contains(name))
        throw AlreadyConnectedCallable(name);

    callables.insert({std::move(name), std::move(callable)});
}

template <typename... Args>
void Event<Args...>::disconnect(const std::string& id) {
    callables.erase(id);
}

template <typename... Args>
void Event<Args...>::fire(Args... args) {
    std::ranges::for_each(callables,
                          [&args...](std::pair<std::string, Callable<Args...>> callable) {
                              callable.second(args...);
                          });
}
