#include "Subject.h"

#include <utility>

#include <bits/ranges_algo.h>

Subject::UnregisteredEvent::UnregisteredEvent(const std::string& eventName):
        std::invalid_argument("Event " + eventName + " is not registered for this subject") {}

Subject::Subject() = default;

Subject::Subject(const Subject& other) = default;

Subject& Subject::operator=(const Subject& other) {
    if (this == &other)
        return *this;

    events = other.events;
    return *this;
}

Subject::Subject(Subject&& other) noexcept: events(std::move(other.events)) {}

Subject& Subject::operator=(Subject&& other) noexcept {
    if (this == &other)
        return *this;

    events = std::move(other.events);
    return *this;
}

Subject::~Subject() {
    std::ranges::for_each(events, [](const auto& pair) { delete pair.second; });
}

Subject::AlreadyRegisteredEvent::AlreadyRegisteredEvent(const std::string& eventName):
        std::invalid_argument("Event " + eventName + " is already registered for this subject") {}

#define INVALID_EVENT                                                                    \
    "The signal you are trying to connect/call has a different signature.\n"             \
    "If you are sending the arguments correctly to connect()/emit(), either explicitly " \
    "specify the template parameters of the method or use explicit construction of the " \
    "type you register the signal with. For example: if you registered the signal with " \
    "std::string and then sent a string literal to connect()/emit(), it will be "        \
    "interpreted as a const char* instead of std::string."

Subject::InvalidEvent::InvalidEvent(): std::runtime_error(INVALID_EVENT) {}

void Subject::unregisterEvent(const std::string& name) {
    if (const size_t deleted = events.erase(name); deleted == 0)
        throw UnregisteredEvent(name);
}
