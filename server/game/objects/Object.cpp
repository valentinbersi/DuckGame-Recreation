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

Object& Object::parent() const {
    if (_parent == nullptr)
        throw RootObject();

    return *_parent;
}

#define NULL_CHILD "newChild is nullptr"
#define CHILD_HAS_PARENT "newChild already has a parent"
#define EMPTY_NAME "name is empty"

void Object::addChild(std::string name, Object* newChild) {
    if (newChild == nullptr)
        throw std::invalid_argument(NULL_CHILD);

    if (newChild->_parent != nullptr)
        throw std::invalid_argument(CHILD_HAS_PARENT);

    if (name.empty())
        throw std::invalid_argument(EMPTY_NAME);

    if (children.contains(name))
        throw AlreadyAddedChild(name);

    newChild->connect<Object, Object&>(eventName(Events::TREE_ENTERED),
                                       {getReference<Object>(), &Object::onTreeEntered});

    newChild->connect<Object, Object&>(eventName(Events::TREE_EXITED),
                                       {getReference<Object>(), &Object::onTreeExited});

    children.emplace(std::move(name), newChild);

    fire<Object, Object&>(eventName(Events::TREE_ENTERED), *newChild);
    newChild->forAllChildren([this](Object& child) {
        fire<Object, Object&>(eventName(Events::TREE_ENTERED), child);
    });
}

void Object::forAllChildren(const std::function<void(Object&)>& f) {
    std::ranges::for_each(children,
                          [&f](const std::pair<std::string, Object*>& child) { f(*child.second); });
}

#define CHILD_NAME "Child with name"
#define ALREADY_EXISTS " already exists."

Object::AlreadyAddedChild::AlreadyAddedChild(const std::string& name):
        std::runtime_error(CHILD_NAME + name + ALREADY_EXISTS) {}

#define NOT_IN_TREE " is not in child tree."

Object::ChildNotInTree::ChildNotInTree(const std::string& name):
        std::out_of_range(CHILD_NAME + name + NOT_IN_TREE) {}

#define NO_PARENT "Object has no parent"

Object::RootObject::RootObject(): std::logic_error(NO_PARENT) {}

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

std::unique_ptr<Object> Object::removeChild(const std::string& name) {
    const HashMap<std::string, Object*>::node_type child(children.extract(name));

    if (child.empty())
        throw ChildNotInTree(name);

    fire<Object, Object&>(eventName(Events::TREE_EXITED), *child.mapped());
    child.mapped()->_parent = nullptr;
    return std::unique_ptr<Object>(child.mapped());
}

void Object::transferChild(std::string name, Object& parent) {
    addChild(std::move(name), std::move(parent.removeChild(name)));
}

Object& Object::getChild(const std::string& name) const { return *children.at(name); }

bool Object::hasChildren() const { return not children.empty(); }

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
