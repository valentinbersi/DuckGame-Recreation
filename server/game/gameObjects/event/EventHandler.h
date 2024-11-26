#pragma once

#include <functional>
#include <memory>
#include <utility>

class GameObject;

namespace gameObject {
/**
 * Thrown when trying to call a method on an invalid object
 */
struct InvalidObject final: std::runtime_error {
    InvalidObject();
};

template <typename... Args>
struct EventHandlerBase {
    EventHandlerBase() = default;
    EventHandlerBase(const EventHandlerBase& other) = delete;
    EventHandlerBase& operator=(const EventHandlerBase& other) = delete;
    EventHandlerBase(EventHandlerBase&& other) noexcept = delete;
    EventHandlerBase& operator=(EventHandlerBase&& other) noexcept = delete;
    virtual ~EventHandlerBase() = default;

    /**
     * Call the method on the object. The object given at the construction must still be valid at
     * the time of the call
     * @param args The arguments to pass to the method
     * @throw std::runtime_error if the inner object has expired
     */
    virtual void operator()(Args... args) const = 0;

    /**
     * Check if the object used to instantiate this method is still valid
     * @return true if the object used to instantiate this method is still valid
     */
    [[nodiscard]] virtual bool isValid() const = 0;
};

/**
 * A wrapper for a GameObject class eventHandler,
 * its purpose is to wrap a GameObject class method and use it as an event handler.
 * @tparam CallerClass The class that the method wrapped by this EventHandler belongs to
 * @tparam Args The arguments of the method
 */
template <typename CallerClass, typename... Args>
class EventHandler final: public EventHandlerBase<Args...> {
    // Assert that the derived class is a subclass of GameObject
    static_assert(std::is_base_of_v<GameObject, CallerClass>,
                  "DerivedClass is not a subclass of GameObject");

    constexpr static auto INVALID_OBJECT =
            "The method was called over an object that no longer exists";

    constexpr static auto INVALID_CALL = "Method called on nullptr object. Probably you are trying "
                                         "to call a method on a moved object.";

    constexpr static auto NULL_OBJECT = "The object given to the EventHandler is null";

    constexpr static auto BAD_CALLER_CLASS = "Downcast from OwnerObject to CallerClass failed";

    /**
     * The object to call the method on
     */
    std::weak_ptr<GameObject> object;

    /**
     * The method to call, taking the object as the first argument
     */
    std::function<void(CallerClass*, Args...)> method;

public:
    EventHandler() = delete;
    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;
    EventHandler(EventHandler&& other) noexcept = delete;
    EventHandler& operator=(EventHandler&& other) noexcept = delete;

    /**
     * Construct a Method wrapper for the given object and method
     * @param object The object to call the method on
     * @param method The method to call
     * @throw std::invalid_argument if the given object is null
     */
    EventHandler(std::weak_ptr<GameObject> object,
                 std::function<void(CallerClass*, Args...)> method);

    /**
     * Call the method on the object. The object given at the construction must still be valid
     * @param args The arguments to pass to the method
     * @tparam CallerClass This template argument should only be used if trying to call a parent's
     * class event from a derived class, otherwise it can be left empty
     * @throw std::runtime_error if the inner object is null (probably moved)
     */
    void operator()(Args... args) const override;

    /**
     * Check if the object used to instantiate this method is still valid
     * @return true if the object used to instantiate this method is still valid
     */
    [[nodiscard]] bool isValid() const override;

    /**
     * Function for easier event handler creation
     * @return a unique pointer to the created event handler
     */
    static std::unique_ptr<EventHandler> create(std::weak_ptr<CallerClass> object,
                                                std::function<void(CallerClass*, Args...)> method);
};

template <typename CallerClass, typename... Args>
EventHandler<CallerClass, Args...>::EventHandler(std::weak_ptr<GameObject> object,
                                                 std::function<void(CallerClass*, Args...)> method):
        object(std::move(object)), method(std::move(method)) {
    if (this->object.expired())
        throw std::invalid_argument(NULL_OBJECT);
}

template <typename CallerClass, typename... Args>
void EventHandler<CallerClass, Args...>::operator()(Args... args) const {
    const std::shared_ptr<GameObject> ownedObject = object.lock();

    // if (ownedObject == nullptr)
    //     throw std::runtime_error(INVALID_CALL);

    auto castedObject = dynamic_cast<CallerClass*>(ownedObject.get());

    if (castedObject == nullptr)
        throw std::runtime_error(INVALID_CALL);

    method(castedObject, args...);
}

template <typename CallerClass, typename... Args>
bool EventHandler<CallerClass, Args...>::isValid() const {
    return !object.expired();
}

template <typename CallerClass, typename... Args>
std::unique_ptr<EventHandler<CallerClass, Args...>> EventHandler<CallerClass, Args...>::create(
        std::weak_ptr<CallerClass> object, std::function<void(CallerClass*, Args...)> method) {
    return std::make_unique<EventHandler>(std::move(object), std::move(method));
}
}  // namespace gameObject
