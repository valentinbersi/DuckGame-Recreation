#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "Event.h"
#include "Types.h"

/**
 * A subject of the observer pattern. Differs from the observer pattern in the way that it doesn't
 * register observers, but callables.
 */
class Subject {
    HashMap<std::string, std::unique_ptr<EventBase>> events;

protected:
    /**
     * Thrown when trying to register an already registered signal
     */
    class AlreadyRegisteredEvent final: public std::invalid_argument {
    public:
        explicit AlreadyRegisteredEvent(const std::string& eventName);
    };

    /**
     * Thrown when trying to connect or emit a signal with a different signature
     */
    class InvalidSignal final: public std::runtime_error {
    public:
        explicit InvalidSignal();
    };

    /**
     * Register an event with the given name and argument types
     * @param name The name of the event
     * @tparam Args The types of the arguments to pass to the callables
     * @throws AlreadyRegisteredEvent if there's already an event with this name
     */
    template <typename... Args>
    void registerEvent(const std::string& name);

    /**
     * Unregister an event with the given name
     * @param name The name of the event
     * @throws UnregisteredEvent If the event is not registered
     */
    void unregisterEvent(const std::string& name);

    /**
     * Fire the event with the given name
     * @param name The name of the event
     * @param args The arguments to pass to the callable
     * @tparam Args The types of the arguments to pass to the callable. It's not mandatory to
     * specify these because the compiler can infer them, but sometimes types like const char*
     * and std::string are confused.
     * @throws UnregisteredEvent If the event is not registered
     * @throws InvalidSignal If the event has different arguments
     * */
    template <typename... Args>
    void emit(const std::string& name, Args... args);

public:
    /**
     * Thrown when trying to connect or emit an unregistered event
     */
    class UnregisteredEvent final: public std::invalid_argument {
    public:
        explicit UnregisteredEvent(const std::string& eventName);
    };

    Subject();
    Subject(const Subject& other);
    Subject& operator=(const Subject& other);
    Subject(Subject&& other) noexcept;
    Subject& operator=(Subject&& other) noexcept;

    /**
     * Connect a callable to the event with the given name
     * @param to The name of the event
     * @param callable The callable to connect
     * @tparam Args The types of the arguments to pass to the callable
     * @throws UnregisteredEvent If the event is not registered
     */
    template <typename... Args>
    void connect(const std::string& to, Callable<Args...> callable);
};

template <typename... Args>
void Subject::registerEvent(const std::string& name) {
    if (events.find(name) == events.cend())
        throw AlreadyRegisteredEvent(name);

    events[name] = std::make_unique<Event<Args...>>();
}

template <typename... Args>
void Subject::connect(const std::string& to, Callable<Args...> callable) {
    if (const auto it = events.find(to); it != events.end()) {
        if (auto signal = dynamic_cast<Event<Args...>*>(it->second.get()))
            signal->connect(callable);
        else
            throw InvalidSignal();

    } else {
        throw UnregisteredEvent(to);
    }
}

template <typename... Args>
void Subject::emit(const std::string& name, Args... args) {
    if (const auto it = events.find(name); it != events.end()) {
        if (auto signal = dynamic_cast<Event<Args...>*>(it->second.get()))
            signal->emit(args...);
        else
            throw InvalidSignal();

    } else {
        throw UnregisteredEvent(name);
    }
}
