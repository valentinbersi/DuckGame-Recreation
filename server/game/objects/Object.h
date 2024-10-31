#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "RefCounted.h"
#include "Startable.h"
#include "Subject.h"
#include "Types.h"
#include "Updatable.h"

/**
 * An object in the game
 */
class Object: public Subject, public RefCounted, public Updatable, public Startable {
    Object* _parent;
    HashMap<std::string, Object*> children;

    /**
     * Called when an object is added to the subtree of this object
     * @param object The child that was added
     */
    void onTreeEntered(Object& object);

    /**
     * Called when an object is removed from the subtree of this object
     * @param object The child that was removed
     */
    void onTreeExited(Object& object);


protected:
    constexpr static auto INVALID_EVENT_TYPE = "Invalid event type";

    /**
     * A constructor for derived classes.
     * Initializes the signals
     */
    explicit Object(Object* parent);

    /**
     * Add a child to the object
     * @param name The name of the child. If the name is already taken, an exception is thrown.
     * @param newChild The child to add.
     */
    void addChild(std::string name, Object* newChild);

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

    Object();
    Object(const Object& other);
    Object& operator=(const Object& other);
    Object(Object&& other) noexcept;
    Object& operator=(Object&& other) noexcept;
    ~Object() override;

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
    void removeChild(const std::string& name);

    /**
     * Get a child of the object.
     * @param name The name of the child to get
     * @return A reference to the child
     */
    Object& getChild(const std::string& name) const;

    /**
     * Get the parent of the object.
     * @return A reference to the parent
     */
    Object& parent() const;

    /**
     * The events the Object class has
     */
    enum class Events : u8 {
        /**
         * A child entered the tree
         */
        TREE_ENTERED,
        /**
         * A child exited the tree
         */
        TREE_EXITED
    };

    /**
     * Get the event name of an event type
     * @param eventType The event type
     * @return The event name
     */
    static std::string eventName(Events eventType);
};
