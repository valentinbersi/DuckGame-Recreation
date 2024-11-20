#include "GameObject.h"

#include <memory>
#include <utility>

#include "EventHandler.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...)                                      \
    std::make_unique<gameObject::EventHandler<GameObject, __VA_ARGS__>>( \
            getReference<GameObject>(), Function)

void GameObject::onTreeEntered(GameObject* object) {
    fire(eventName(Events::TREE_ENTERED), object);
}

void GameObject::onTreeExited(GameObject* object) { fire(eventName(Events::TREE_EXITED), object); }

GameObject::GameObject(GameObject* parent): _parent(parent) {
    registerEvent<GameObject*>(eventName(Events::TREE_ENTERED));
    registerEvent<GameObject*>(eventName(Events::TREE_EXITED));
}

#define NULL_CHILD "newChild is nullptr"
#define CHILD_HAS_PARENT "newChild already has a parent"
#define EMPTY_NAME "name is empty"

void GameObject::addChild(std::string name, GameObject* newChild) {
    if (newChild == nullptr)
        throw std::invalid_argument(NULL_CHILD);

    if (newChild->_parent != nullptr)
        throw std::invalid_argument(CHILD_HAS_PARENT);

    if (name.empty())
        throw std::invalid_argument(EMPTY_NAME);

    if (children.contains(name))
        throw AlreadyAddedChild(name);

    newChild->connect(eventName(Events::TREE_ENTERED),
                      eventHandler(&GameObject::onTreeEntered, GameObject*));

    newChild->connect(eventName(Events::TREE_EXITED),
                      eventHandler(&GameObject::onTreeExited, GameObject*));

    children.emplace(std::move(name), newChild);

    fire(eventName(Events::TREE_ENTERED), newChild);
    for (auto& [name, child]: newChild->children) fire(eventName(Events::TREE_ENTERED), child);
}

void GameObject::forAllChildren(const std::function<void(GameObject*)>& f) {
    for (const auto& [name, child]: children) f(child);
}

#define CHILD_NAME "Child with name"
#define ALREADY_EXISTS " already exists."

GameObject::AlreadyAddedChild::AlreadyAddedChild(const std::string& name):
        std::runtime_error(CHILD_NAME + name + ALREADY_EXISTS) {}

#define NOT_IN_TREE " is not in child tree."

GameObject::ChildNotInTree::ChildNotInTree(const std::string& name):
        std::out_of_range(CHILD_NAME + name + NOT_IN_TREE) {}

GameObject::GameObject(): _parent(nullptr) {}

#define NO_PARENT "Object has no parent"

GameObject::~GameObject() {
    for (auto& [name, child]: children) delete child;
}

void GameObject::start() {}

void GameObject::update([[maybe_unused]] float delta) {}

void GameObject::updateInternal(const float delta) {
    for (auto& [name, child]: children) {
        child->update(delta);
        child->updateInternal(delta);
    }
}

void GameObject::addChild(std::string name, std::unique_ptr<GameObject> newChild) {
    addChild(std::move(name), newChild.release());
}

std::unique_ptr<GameObject> GameObject::removeChild(const std::string& name) {
    const HashMap<std::string, GameObject*>::node_type child(children.extract(name));

    if (child.empty())
        throw ChildNotInTree(name);

    fire(eventName(Events::TREE_EXITED), child.mapped());
    for (auto& [name, child]: children) fire(eventName(Events::TREE_EXITED), child);

    child.mapped()->_parent = nullptr;
    return std::unique_ptr<GameObject>(child.mapped());
}

void GameObject::transferChild(std::string name, GameObject& parent) {
    addChild(std::move(name), parent.removeChild(name));
}

GameObject* GameObject::getChild(const std::string& name) const { return children.at(name); }

bool GameObject::isParent() const { return not children.empty(); }

GameObject* GameObject::parent() const { return _parent; }

bool GameObject::isRoot() const { return _parent == nullptr; }

#define TREE_ADDED_NAME "TreeEntered"
#define TREE_EXITED_NAME "TreeExited"

std::string GameObject::eventName(const Events eventType) {
    switch (eventType) {
        case Events::TREE_ENTERED:
            return TREE_ADDED_NAME;
        case Events::TREE_EXITED:
            return TREE_EXITED_NAME;
        default:
            throw std::invalid_argument(INVALID_EVENT_TYPE);
    }
}
