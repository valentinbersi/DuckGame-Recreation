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
        return name;

    for (u64 i = 0; i < std::numeric_limits<u64>::max(); ++i)
        if (std::string newName = name + std::to_string(i); not children.contains(newName))
            return newName;

    throw NoMoreNamesAvailable(name);
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
    newChild->name = name;

    newChild->connect(Events::TreeEntered, eventHandler(&GameObject::onTreeEntered, GameObject*));
    newChild->connect(Events::TreeExited, eventHandler(&GameObject::onTreeExited, GameObject*));

    newChild->_parent = this;

    children.emplace(std::move(name), newChild);

    // newChild->start();
    // newChild->startInternal();

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

GameObject::GameObject(): _parent(nullptr), active(true) {
    registerEvent<GameObject*>(Events::TreeEntered);
    registerEvent<GameObject*>(Events::TreeExited);
}

#define NO_PARENT "Object has no parent"

GameObject::~GameObject() {
    for (const GameObject* child: children | std::views::values) delete child;
}

void GameObject::start() {}

void GameObject::update([[maybe_unused]] float delta) {}

void GameObject::finish() {}

void GameObject::updateInternal(const float delta) {
    for (GameObject* child: children | std::views::values) {
        if (not child->active)
            continue;

        child->update(delta);
        child->updateInternal(delta);
    }

    for (const GameObject* child: childrenToRemove) {
        children.erase(child->name);
        delete child;
    }

    childrenToRemove.clear();
}

void GameObject::startInternal() {
    for (GameObject* child: children | std::views::values) {
        if (not child->active)
            continue;

        child->start();
        child->startInternal();
    }
}

void GameObject::finishInternal() {
    for (GameObject* child: children | std::views::values) {
        if (not child->active)
            continue;

        child->finish();
        child->finishInternal();
    }
}

void GameObject::addChild(std::string name, std::unique_ptr<GameObject> newChild) {
    addChild(std::move(name), newChild.release());
}

GameObject* GameObject::removeChild(const std::string& name) {
    GameObject* child = children.at(name);

    fire(Events::TreeExited, child);
    for (GameObject* object: child->children | std::views::values) fire(Events::TreeExited, object);

    child->_parent = nullptr;
    // child->name = "";
    child->finish();
    child->finishInternal();
    child->active = false;
    childrenToRemove.push_back(child);
    return child;
}

GameObject* GameObject::removeChild(const GameObject* object) { return removeChild(object->name); }

void GameObject::transferChild(const std::string& name, GameObject& parent) {
    addChild(name, parent.removeChild(name));
}

void GameObject::transferChild(const GameObject* object, GameObject& parent) {
    transferChild(object->name, parent);
}

bool GameObject::isParent() const { return not children.empty(); }

bool GameObject::isRoot() const { return _parent == nullptr; }
