#include "Subject.h"

#include <bits/ranges_algo.h>

#define EVENT "Event "
#define ALREADY_REGISTERED " is already registered for this subject"

namespace gameObject {
Subject::AlreadyRegisteredEvent::AlreadyRegisteredEvent(const std::string& eventName):
        std::invalid_argument(EVENT + eventName + ALREADY_REGISTERED) {}

#define INVALID_EVENT                                                                    \
    "The signal you are trying to connect/call has a different signature.\n"             \
    "If you are sending the arguments correctly to connect()/emit(), either explicitly " \
    "specify the template parameters of the method or use explicit construction of the " \
    "type you register the signal with. For example: if you registered the signal with " \
    "std::string and then sent a string literal to connect()/emit(), it will be "        \
    "interpreted as a const char* instead of std::string."

Subject::InvalidEvent::InvalidEvent(): std::runtime_error(INVALID_EVENT) {}

#define NOT_REGISTERED " is not registered for this subject"

Subject::UnregisteredEvent::UnregisteredEvent(const std::string& eventName):
        std::invalid_argument(EVENT + eventName + NOT_REGISTERED) {}

void Subject::unregisterEvent(const std::string& name) {
    const auto event = events.extract(name);

    if (event.empty())
        throw UnregisteredEvent(name);

    delete event.mapped();
}

Subject::Subject() noexcept = default;

Subject::~Subject() {
    std::ranges::for_each(
            events, [](const std::pair<std::string, EventBase*>& event) { delete event.second; });
}
}  // namespace gameObject
