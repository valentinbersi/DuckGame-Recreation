#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#include "Event.h"
#include "Types.h"

/**
 * A subject of the observer pattern. Differs from the observer pattern in the way that it doesn't
 * register observers, but callables.
 */
class Subject {
    HashMap<std::string, EventBase*> events;

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
    class InvalidEvent final: public std::runtime_error {
    public:
        explicit InvalidEvent();
    };

    /**
     * Register an event with the given name and argument types
     * @param name The name of the event
     * @tparam Object The type of the object that the callables are member functions of
     * @tparam Args The types of the arguments to pass to the callables
     * @throws AlreadyRegisteredEvent if there's already an event with this name
     */
    template <typename Object, typename... Args>
    void registerEvent(std::string name);

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
     * @tparam Object The type of the object that the callable belongs to
     * @tparam Args The types of the arguments to pass to the callable. It's not mandatory to
     * specify these because the compiler can infer them, but sometimes types like const char*
     * and std::string are confused.
     * @throws std::out_of_range If the event is not registered
     * @throws InvalidEvent If the event has different arguments type
     * */
    template <typename Object, typename... Args>
    void fire(const std::string& name, Args... args);

public:
    /**
     * Thrown when trying to connect or emit an unregistered event
     */
    class UnregisteredEvent final: public std::invalid_argument {
    public:
        explicit UnregisteredEvent(const std::string& eventName);
    };

    Subject() noexcept;
    Subject(const Subject& other) noexcept;
    Subject& operator=(const Subject& other) noexcept;
    Subject(Subject&& other) noexcept;
    Subject& operator=(Subject&& other) noexcept;
    virtual ~Subject();

    /**
     * Connect a callable to the event with the given name
     * @param to The name of the event
     * @param method The callable to connect
     * @tparam Object The type of the object that the method belongs to
     * @tparam Args The types of the arguments to pass to the callable
     * @throws std::out_of_range If the event is not registered
     * @throws InvalidEvent If the event has different arguments type
     */
    template <typename Object, typename... Args>
    void connect(const std::string& to, Method<Object, void, Args...> method);
};

template <typename Object, typename... Args>
void Subject::registerEvent(std::string name) {
    if (events.contains(name))
        throw AlreadyRegisteredEvent(name);

    events.emplace(std::move(name), new Event<Object, Args...>());
}

template <typename Object, typename... Args>
void Subject::fire(const std::string& name, Args... args) {
    auto event = dynamic_cast<Event<Object, Args...>*>(events.at(name));

    if (event == nullptr)
        throw InvalidEvent();

    event->fire(args...);
}


template <typename Object, typename... Args>
void Subject::connect(const std::string& to, Method<Object, void, Args...> method) {
    auto event = dynamic_cast<Event<Object, Args...>*>(events.at(to));

    if (event == nullptr)
        throw InvalidEvent();

    event->connect(std::move(method));
}
