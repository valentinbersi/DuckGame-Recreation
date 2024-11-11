#pragma once

#include <list>

#include <bits/ranges_algo.h>

#include "EventHandler.h"

namespace gameObject {
/**
 * A struct for referencing different template instantiations of Events
 * @tparam Args The arguments of the EventHandlers
 */
struct EventBase {
    EventBase() = default;
    EventBase(const EventBase& other) = delete;
    EventBase& operator=(const EventBase& other) = delete;
    EventBase(EventBase&& other) noexcept = delete;
    EventBase& operator=(EventBase&& other) noexcept = delete;
    virtual ~EventBase() = default;
};

/**
 * An Event for Objects in the game
 * @tparam CreatorClass The class that creates this event
 * @tparam Args The arguments of the EventHandlers
 */
template <typename... Args>
class Event final: public EventBase {
    std::list<EventHandlerBase<Args...>*> eventHandlers;

public:
    Event() noexcept = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) noexcept = delete;
    Event& operator=(Event&&) noexcept = delete;
    ~Event() override;

    /**
     * Connect an event handler to the event
     * @param eventHandler the event handler to connect
     */
    void connect(std::unique_ptr<EventHandlerBase<Args...>> eventHandler) noexcept;

    /**
     * Fire the event. This will call all connected methods with the given arguments.
     * @param args The arguments to pass to the callables
     * @tparam CallerClass This template argument should only be used if trying to call a parent's
     * class event from a derived class, otherwise it can be left empty
     */
    void fire(Args... args);
};

template <typename... Args>
Event<Args...>::~Event() {
    std::ranges::for_each(eventHandlers, [](const EventHandlerBase<Args...>* eventHandler) {
        delete eventHandler;
    });
}

template <typename... Args>
void Event<Args...>::connect(std::unique_ptr<EventHandlerBase<Args...>> eventHandler) noexcept {
    eventHandlers.push_back(eventHandler.release());
}

template <typename... Args>
void Event<Args...>::fire(Args... args) {
    eventHandlers.remove_if([&args...](const EventHandlerBase<Args...>* eventHandler) -> bool {
        if (not eventHandler->isValid())
            return true;

        (*eventHandler)(args...);
        return false;
    });
}
}  // namespace gameObject
