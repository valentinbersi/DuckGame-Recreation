#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

#include "Event.h"
#include "Types.h"

namespace gameObject {
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
     * @tparam Args The arguments that the event takes
     * @throws AlreadyRegisteredEvent if there's already an event with this name
     */
    template <typename... Args>
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
     * @tparam Args The types of the arguments to pass to the callable. It's not mandatory to
     * specify these because the compiler can infer them, but sometimes types like const char*
     * and std::string are confused.
     * @throws std::out_of_range If the event is not registered
     * @throws InvalidEvent If the event has different arguments type
     * */
    template <typename... Args>
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
    Subject(const Subject& other) noexcept = delete;
    Subject& operator=(const Subject& other) noexcept = delete;
    Subject(Subject&& other) noexcept = delete;
    Subject& operator=(Subject&& other) noexcept = delete;
    virtual ~Subject();

    /**
     * Connect a EventHandler to the event with the given name
     * @param to The name of the event
     * @param eventHandler The EventHandler to connect to the event
     * @tparam CallerClass The class that the method wrapped by the EventHandler belongs to
     * @tparam Args The types of the arguments to pass to the EventHandler
     * @throws std::out_of_range If the event is not registered
     * @throws InvalidEvent If the event has different arguments type
     */
    template <typename CallerClass, typename... Args>
    void connect(const std::string& to,
                 std::unique_ptr<EventHandler<CallerClass, Args...>> eventHandler);
};

template <typename... Args>
void Subject::registerEvent(std::string name) {
    if (events.contains(name))
        throw AlreadyRegisteredEvent(name);

    events.emplace(std::move(name), new Event<Args...>());
}

template <typename... Args>
void Subject::fire(const std::string& name, Args... args) {
    auto event = dynamic_cast<Event<Args...>*>(events.at(name));

    if (event == nullptr)
        throw InvalidEvent();

    event->fire(args...);
}

template <typename CallerClass, typename... Args>
void Subject::connect(const std::string& to,
                      std::unique_ptr<EventHandler<CallerClass, Args...>> eventHandler) {
    auto event = dynamic_cast<Event<Args...>*>(events.at(to));

    if (event == nullptr)
        throw InvalidEvent();

    event->connect(std::move(eventHandler));
}
}  // namespace gameObject
