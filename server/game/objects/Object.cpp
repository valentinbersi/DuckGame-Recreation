#include "Object.h"

#include <memory>
#include <utility>

#include <bits/ranges_algo.h>

#include "Method.h"

void Object::onTreeEntered(Object& object) {
    fire<Object, Object&>(eventName(Events::TREE_ENTERED), object);
}

void Object::onTreeExited(Object& object) {
    fire<Object, Object&>(eventName(Events::TREE_EXITED), object);
}

Object::Object(Object* parent): _parent(parent) {
    registerEvent<Object, Object&>(eventName(Events::TREE_ENTERED));
    registerEvent<Object, Object&>(eventName(Events::TREE_EXITED));
}

#define NULL_CHILD "newChild is nullptr"
#define EMPTY_NAME "name is empty"

void Object::addChild(std::string name, Object* newChild) {
    if (newChild == nullptr)
        throw std::invalid_argument(NULL_CHILD);

    if (name.empty())
        throw std::invalid_argument(EMPTY_NAME);

    if (children.contains(name))
        throw AlreadyAddedChild(name);

    newChild->connect<Object, Object&>(eventName(Events::TREE_ENTERED),
                                       {weakReference<Object>(), &Object::onTreeEntered});

    newChild->connect<Object, Object&>(eventName(Events::TREE_EXITED),
                                       {weakReference<Object>(), &Object::onTreeExited});

    children.insert({std::move(name), newChild});
    newChild->_parent = this;
    fire<Object, Object&>(eventName(Events::TREE_ENTERED), *newChild);
}

Object::AlreadyAddedChild::AlreadyAddedChild(const std::string& name):
        std::runtime_error("Child with name " + name + " already exists.") {}

Object::ChildNotInTree::ChildNotInTree(const std::string& name):
        std::runtime_error("Child with name " + name + " is not in child tree.") {}

Object::Object(): Object(nullptr) {}

Object::Object(const Object& other):
        Subject(other), RefCounted(), _parent(other._parent), children(other.children) {}

Object& Object::operator=(const Object& other) {
    if (this == &other)
        return *this;

    Subject::operator=(other);
    _parent = other._parent;

    std::ranges::for_each(
            children, [](const std::pair<std::string, Object*>& child) { delete child.second; });
    children = other.children;
    return *this;
}

Object::Object(Object&& other) noexcept:
        Subject(std::move(other)),
        RefCounted(),
        _parent(other._parent),
        children(std::move(other.children)) {
    other._parent = nullptr;
}

Object& Object::operator=(Object&& other) noexcept {
    if (this == &other)
        return *this;

    Subject::operator=(std::move(other));
    _parent = other._parent;
    other._parent = nullptr;
    std::ranges::for_each(
            children, [](const std::pair<std::string, Object*>& child) { delete child.second; });
    children = std::move(other.children);
    return *this;
}

Object::~Object() {
    std::ranges::for_each(
            children, [](const std::pair<std::string, Object*>& child) { delete child.second; });
}

void Object::updateInternal(float delta) {
    std::ranges::for_each(children, [delta](const std::pair<std::string, Object*>& child) {
        child.second->updateInternal(delta);
        child.second->update(delta);
    });
}

void Object::addChild(std::string name, std::unique_ptr<Object> newChild) {
    addChild(std::move(name), newChild.release());
}

void Object::removeChild(const std::string& name) {
    const auto child = children.find(name);

    if (child == children.end())
        throw ChildNotInTree(name);

    fire<Object, Object&>(eventName(Events::TREE_EXITED), *child->second);

    delete child->second;
    children.erase(child);
}

Object& Object::getChild(const std::string& name) const {
    const auto child = children.find(name);

    if (child == children.end())
        throw ChildNotInTree(name);

    return *child->second;
}

Object& Object::parent() const { return *_parent; }

#define TREE_ADDED_NAME "TreeEntered"
#define TREE_EXITED_NAME "TreeExited"

std::string Object::eventName(const Events eventType) {
    switch (eventType) {
        case Events::TREE_ENTERED:
            return TREE_ADDED_NAME;
        case Events::TREE_EXITED:
            return TREE_EXITED_NAME;
        default:
            throw std::invalid_argument(INVALID_EVENT_TYPE);
    }
}
