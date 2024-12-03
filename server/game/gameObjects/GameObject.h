#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Finishable.h"
#include "Startable.h"
#include "Subject.h"
#include "TrackedReference.h"
#include "Types.h"
#include "Updatable.h"

/**
 * An object in the game.\n
 * The objects organize in a tree way, where each object can have children.\n
 * Every object is responsible for managing the memory of its children,
 * because of this, objects are not copyable or movable, and they can only have one parent.\n
 * Callers don't own pointers returned by Objects, in the same way,
 * any raw pointer passed as argument inside Objects does not hold ownership of the
 * underlying object.\n
 */
class GameObject:
        public gameObject::Subject,
        public TrackedReference,
        public Updatable,
        public Startable,
        public Finishable {
    std::string name;
    GameObject* _parent;
    HashMap<std::string, GameObject*> children;
    std::list<GameObject*> childrenToRemove;
    bool active;

    /**
     * Object class handler for tree entered event.\n
     * It simply fires the event so parents are notified of a new child in the tree
     * @param object The child that was added
     */
    virtual void onTreeEntered(GameObject* object);

    /**
     * Object class handler for tree exited event.\n
     * It simply fires the event so parents are notified of a new child in the tree.
     * @param object The child that was removed
     */
    virtual void onTreeExited(GameObject* object);

    /**
     * Checks if there's a child with the same name. If true returns a valid name for that child,
     * otherwise returns the same name.
     * @param name The name to check
     * @return A valid name for the child
     */
    std::string findAvaiableName(std::string name) const;

protected:
    constexpr static auto INVALID_EVENT_TYPE = "Invalid event type";

    /**
     * Add a child to the object
     * @param name The name of the child. If the name is already taken, an exception is thrown.
     * @param newChild The child to add.
     * @throws  std::invalid_argument If newChild is nullptr
     * @throws  std::invalid_argument If newChild already has a parent
     * @throws  std::invalid_argument If name is empty
     * @throws  NoMoreNamesAvailable If the name is already taken
     */
    void addChild(std::string name, GameObject* newChild);

    /**
     * Apply the given function to all children
     * @param f The function to apply, should not throw exceptions
     */
    void forAllChildren(const std::function<void(GameObject*)>& f);

    /**
     * Apply the given function to a child
     * @param name The name of the child
     * @param f The function to apply
     * @tparam Ret The return type of the function
     * @return The result of the function
     * @throws std::out_of_range If the child is not found
     */
    template <typename Ret>
    Ret applyToChild(const std::string& name, const std::function<Ret(GameObject*)>& f);

public:
    struct Events {
        constexpr static auto TreeEntered = "TreeEntered";
        constexpr static auto TreeExited = "TreeExited";
    };

    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    struct NoMoreNamesAvailable final: std::runtime_error {
        explicit NoMoreNamesAvailable(const std::string& name);
    };

    /**
     * An exception thrown when trying to add a child with a name that is already taken
     */
    struct ChildNotInTree final: std::out_of_range {
        explicit ChildNotInTree(const std::string& name);
    };

    GameObject();
    GameObject(const GameObject& other) = delete;
    GameObject& operator=(const GameObject& other) = delete;
    GameObject(GameObject&& other) noexcept = delete;
    GameObject& operator=(GameObject&& other) noexcept = delete;
    ~GameObject() override;

    /**
     * Does nothing on object
     */
    void start() override;

    /**
     * Does nothing on object
     * @param delta The time since the last update
     */
    void update(float delta) override;

    /**
     * Does nothing on object
     */
    void finish() override;

    /**
     * Updates the children of the object
     */
    void updateInternal(float delta) override;

    /**
     * Starts the children of the object
     */
    void startInternal() override;

    /**
     * Finishes the children of the object
     */
    void finishInternal() override;

    /**
     * Add a child to the object
     * @param name The name of the child. If the name is already taken, an exception is thrown.
     * @param newChild The child to add.
     * @throws  std::invalid_argument If newChild is nullptr
     * @throws  std::invalid_argument If name is empty
     * @throws std::invalid_argument if newChild already has a parent
     * @throws  NoMoreNamesAvailable If the name is already taken
     */
    void addChild(std::string name, std::unique_ptr<GameObject> newChild);

    /**
     * Remove a child from the object
     * @param name The name of the child to remove
     * @return A pointer to the removed child
     */
    GameObject* removeChild(const std::string& name);

    /**
     * Remove a child from the object
     * @param object The child to remove
     * @return A pointer to the removed child
     */
    GameObject* removeChild(const GameObject* object);

    /**
     * Transfer a child from another object to this
     * @param name The name of the child to transfer
     * @param parent The parent object to transfer the child from
     */
    void transferChild(const std::string& name, GameObject& parent);

    /**
     * Transfer a child from another object to this
     * @param object The child to transfer
     * @param parent The parent object to transfer the child from
     */
    void transferChild(const GameObject* object, GameObject& parent);

    /**
     * Get a child of the object.
     * @param name The name of the child to get
     * @return A reference to the child
     * @throws std::out_of_range If the child is not found
     */
    template <typename ObjectType = GameObject>
    ObjectType* getChild(const std::string& name) const;

    /**
     * Check if the object has children
     * @return True if the object has children, false otherwise
     */
    bool isParent() const;

    /**
     * Get the parent of the object
     * @return A reference to the parent
     * @throws RootObject If the object has no parent
     */
    template <typename ObjectType = GameObject>
    ObjectType* parent() const;

    /**
     * Check if the object is the root object
     * @return True if the object is the root object, false otherwise
     */
    bool isRoot() const;

    /**
     * Get the root object of the tree
     * @return A reference to the root object
     */
    template <typename ObjectType = GameObject>
    ObjectType* getRoot();
};

template <typename Ret>
Ret GameObject::applyToChild(const std::string& name, const std::function<Ret(GameObject*)>& f) {
    return f(children.at(name));
}

template <typename ObjectType>
ObjectType* GameObject::getChild(const std::string& name) const {
    static_assert(std::is_base_of_v<GameObject, ObjectType>,
                  "Cannot get child of something that is not a GameObject");

    return dynamic_cast<ObjectType*>(children.at(name));
}

template <typename ObjectType>
ObjectType* GameObject::parent() const {
    static_assert(std::is_base_of_v<GameObject, ObjectType>,
                  "Cannot get child of something that is not a GameObject");

    return dynamic_cast<ObjectType*>(_parent);
}

template <typename ObjectType>
ObjectType* GameObject::getRoot() {
    if (isRoot())
        return dynamic_cast<ObjectType*>(this);

    return _parent->getRoot<ObjectType>();
}
