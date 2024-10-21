#include "Object.h"

#define CHILD_ADDED_NAME "ChildAdded"
#define CHILD_REMOVED_NAME "ChildRemoved"
#define INVALID_EVENT_TYPE "Invalid Event Type"

Object::Object(Object* parent): _parent(parent) {
    registerEvent<Object&>(getEventName(EventTypes::CHILD_ADDED));
    registerEvent<Object&>(getEventName(EventTypes::CHILD_REMOVED));
}

Object::AlreadyAddedChild::AlreadyAddedChild(const std::string& name):
        std::runtime_error("Child with name " + name + " already exists.") {}

Object::ChildNotInTree::ChildNotInTree(const std::string& name):
        std::runtime_error("Child with name " + name + " is not in child tree.") {}

Object::Object(): Object(nullptr) {}

Object::Object(const Object& other):
        Subject(other), _parent(other._parent), children(other.children) {}

Object& Object::operator=(const Object& other) {
    if (this == &other)
        return *this;

    Subject::operator=(other);
    _parent = other._parent;
    children = other.children;
    return *this;
}

Object::Object(Object&& other) noexcept:
        Subject(std::move(other)), _parent(other._parent), children(std::move(other.children)) {
    other._parent = nullptr;
}

Object& Object::operator=(Object&& other) noexcept {
    if (this == &other)
        return *this;

    Subject::operator=(std::move(other));
    _parent = other._parent;
    other._parent = nullptr;
    children = std::move(other.children);
    return *this;
}

void Object::updateInternal(float delta) {
    std::for_each(children.begin(), children.end(),
                  [delta](const std::pair<std::string, std::unique_ptr<Object>>& child) {
                      child.second->updateInternal(delta);
                      child.second->update(delta);
                  });
}

void Object::addChild(std::string name, std::unique_ptr<Object> newChild) {
    if (children.contains(name))
        throw AlreadyAddedChild(name);

    Object* newChildPtr = newChild.release();
    newChildPtr->_parent = this;
    children.emplace(std::move(name), newChildPtr);
    emit<Object&>(getEventName(EventTypes::CHILD_ADDED), *newChildPtr);
}

std::unique_ptr<Object> Object::removeChild(const std::string& name) {
    if (!children.contains(name))
        throw ChildNotInTree(name);

    return std::unique_ptr<Object>(children.extract(name).mapped());
}

Object* Object::getChild(const std::string& name) const {
    if (!children.contains(name))
        throw ChildNotInTree(name);

    return children.at(name);
}

Object* Object::parent() const { return _parent; }

std::string Object::getEventName(const EventTypes eventType) {
    switch (eventType) {
        case EventTypes::CHILD_ADDED:
            return CHILD_ADDED_NAME;
        case EventTypes::CHILD_REMOVED:
            return CHILD_REMOVED_NAME;
        default:
            throw std::invalid_argument(INVALID_EVENT_TYPE);
    }
}
