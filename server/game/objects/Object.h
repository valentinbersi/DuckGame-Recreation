#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "GameStatus.h"
#include "Startable.h"
#include "Subject.h"
#include "TrackedReference.h"
#include "Types.h"
#include "Updatable.h"

/**
 * An object in the game
 */
class Object: public Subject, public TrackedReference, public Updatable, public Startable {
    Object* _parent;
    HashMap<std::string, Object*> children;

    /**
     * Called when an object is added to the subtree of this object.\n
     * It simply fires the event so parents are notified of a new child in the tree
     * @param object The child that was added
     */
    void onTreeEntered(Object& object);

    /**
     * Called when an object is removed from the subtree of this object.\n
     * It simply fires the event so parents are notified of a new child in the tree.
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
     * @throws  std::invalid_argument If newChild is nullptr
     * @throws  std::invalid_argument If name is empty
     * @throws  AlreadyAddedChild If the name is already taken
     */
    virtual void addChild(std::string name, Object* newChild);

    /**
     * Apply the given function to all children
     * @param f The function to apply, should not throw exceptions
     */
    void forAllChildren(const std::function<void(Object&)>& f);

    /**
     * Apply the given function to a child
     * @param name The name of the child
     * @param f The function to apply
     * @tparam Ret The return type of the function
     * @return The result of the function
     * @throws std::out_of_range If the child is not found
     */
    template <typename Ret>
    Ret applyToChild(const std::string& name, const std::function<Ret(Object&)>& f);

public:
    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    struct AlreadyAddedChild final: std::runtime_error {
        explicit AlreadyAddedChild(const std::string& name);
    };

    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    struct ChildNotInTree final: std::out_of_range {
        explicit ChildNotInTree(const std::string& name);
    };

    /**
     * An exception thrown when trying access the parent of the root object
     */
    struct RootObject final: std::logic_error {
        explicit RootObject();
    };

    struct AddedChildWithChildren final: std::logic_error {
        explicit AddedChildWithChildren();
    };

    Object() = delete;
    Object(const Object& other) = delete;
    Object& operator=(const Object& other) = delete;
    Object(Object&& other) noexcept = delete;
    Object& operator=(Object&& other) noexcept = delete;
    ~Object() override;

    /**
     * Updates the children of the object
     */
    void updateInternal(float delta) override;

    /**
     * Add a child to the object
     * @param name The name of the child. If the name is already taken, an exception is thrown.
     * @param newChild The child to add.
     * @throws  std::invalid_argument If newChild is nullptr
     * @throws  std::invalid_argument If name is empty
     * @throws  AlreadyAddedChild If the name is already taken
     */
    void addChild(std::string name, std::unique_ptr<Object> newChild);

    /**
     * Remove a child from the object
     * @param name The name of the child to remove
     * @return A pointer to the removed child
     */
    std::unique_ptr<Object> removeChild(const std::string& name);

    /**
     * Get a child of the object.
     * @param name The name of the child to get
     * @return A reference to the child
     * @throws std::out_of_range If the child is not found
     */
    Object& getChild(const std::string& name) const;

    /**
     * Check if the object has children
     * @return True if the object has children, false otherwise
     */
    bool hasChildren() const;

    /**
     * Get the status of the object
     * @return The status of the object
     */
    virtual GameStatus status() = 0;

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

template <typename Ret>
Ret Object::applyToChild(const std::string& name, const std::function<Ret(Object&)>& f) {
    return f(children.at(name));
}
