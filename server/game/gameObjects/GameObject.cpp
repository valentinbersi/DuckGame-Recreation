#include "GameObject.h"

#include <limits>
#include <memory>
#include <ranges>
#include <utility>

#include "EventHandler.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<GameObject, __VA_ARGS__>::create(getReference<GameObject>(), Function)

void GameObject::onTreeEntered(GameObject* object) { fire(Events::TreeEntered, object); }

void GameObject::onTreeExited(GameObject* object) { fire(Events::TreeExited, object); }

std::string GameObject::findAvaiableName(std::string name) const {
    if (not children.contains(name))
        return std::move(name);

    for (int i = 0; i < std::numeric_limits<u64>::max(); i++)
        if (std::string newName = name + std::to_string(i); not children.contains(newName))
            return newName;

    throw NoMoreNamesAvailable(name);
}

GameObject::GameObject(GameObject* parent): _parent(parent) {
    registerEvent<GameObject*>(Events::TreeEntered);
    registerEvent<GameObject*>(Events::TreeExited);
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

    name = findAvaiableName(name);

    newChild->connect(Events::TreeEntered, eventHandler(&GameObject::onTreeEntered, GameObject*));
    newChild->connect(Events::TreeExited, eventHandler(&GameObject::onTreeExited, GameObject*));

    children.emplace(std::move(name), newChild);

    fire(Events::TreeEntered, newChild);
    for (GameObject* child: newChild->children | std::views::values)
        fire(Events::TreeEntered, child);
}

void GameObject::forAllChildren(const std::function<void(GameObject*)>& f) {
    for (GameObject* child: children | std::views::values) f(child);
}

#define CHILD_NAME "Child with name"
#define CANNOT_BE_ADDED " cannot be added to tree."

GameObject::NoMoreNamesAvailable::NoMoreNamesAvailable(const std::string& name):
        std::runtime_error(CHILD_NAME + name + CANNOT_BE_ADDED) {}

#define NOT_IN_TREE " is not in child tree."

GameObject::ChildNotInTree::ChildNotInTree(const std::string& name):
        std::out_of_range(CHILD_NAME + name + NOT_IN_TREE) {}

GameObject::GameObject(): _parent(nullptr) {}

#define NO_PARENT "Object has no parent"

GameObject::~GameObject() {
    for (const GameObject* child: children | std::views::values) delete child;
}

void GameObject::start() {}

void GameObject::update([[maybe_unused]] float delta) {}

void GameObject::updateInternal(const float delta) {
    for (GameObject* child: children | std::views::values) {
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

    fire(Events::TreeExited, child.mapped());
    for (GameObject* object: child.mapped()->children | std::views::values)
        fire(Events::TreeExited, object);

    child.mapped()->_parent = nullptr;
    return std::unique_ptr<GameObject>(child.mapped());
}

void GameObject::transferChild(const std::string& name, GameObject& parent) {
    addChild(name, parent.removeChild(name));
}

GameObject* GameObject::getChild(const std::string& name) const { return children.at(name); }

bool GameObject::isParent() const { return not children.empty(); }

GameObject* GameObject::parent() const { return _parent; }

bool GameObject::isRoot() const { return _parent == nullptr; }

GameObject* GameObject::getRoot() {
    if (isRoot())
        return this;

    return _parent->getRoot();
}
