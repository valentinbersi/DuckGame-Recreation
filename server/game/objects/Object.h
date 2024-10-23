#pragma once

#include <string>
#include <unordered_map>

#include "Startable.h"
#include "Subject.h"
#include "Types.h"
#include "Updatable.h"

/**
 * An object in the game
 */
class Object: public Subject, public Updatable, public Startable {
    Object* _parent;
    HashMap<std::string, Object*> children;

protected:
    /**
     * A constructor for derived classes.
     * Initializes the signals
     */
    explicit Object(Object* parent);

    /**
     * Get a child of the object.
     * @param name The name of the child to get
     * @return A ptr to the child
     */
    Object* getChild(const std::string& name) const;

    /**
     * Get the parent of the object.
     * @return A ptr to the parent
     */
    Object* parent() const;

public:
    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    class AlreadyAddedChild final: public std::runtime_error {
    public:
        explicit AlreadyAddedChild(const std::string& name);
    };

    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    class ChildNotInTree final: public std::runtime_error {
    public:
        explicit ChildNotInTree(const std::string& name);
    };

    enum class EventTypes { CHILD_ADDED, CHILD_REMOVED };

    Object();
    Object(const Object& other);
    Object& operator=(const Object& other);
    Object(Object&& other) noexcept;
    Object& operator=(Object&& other) noexcept;

    /**
     * Updates the children of the object
     */
    void updateInternal(float delta) override;

    /**
     * Add a child to the object
     * @param name The name of the child. If the name is already taken, an exception is thrown.
     * @param newChild The child to add.
     * @throw
     */
    void addChild(std::string name, std::unique_ptr<Object> newChild);

    /**
     * Remove a child from the object
     * @param name The name of the child to remove
     * @return A pointer to the removed child
     */
    std::unique_ptr<Object> removeChild(const std::string& name);

    /**
     * Get the event name of an event type
     * @param eventType The event type
     * @return The event name
     */
    static std::string getEventName(EventTypes eventType);
};
