#include "Debug.h"

#ifdef DEBUG
#include <iostream>
Debug::Debug(std::ostream& out): out(out) {}

Debug::~Debug() { flush(); }

Debug& Debug::cout() {
    static Debug instance(std::cout);
    return instance;
}

Debug& Debug::cerr() {
    static Debug instance(std::cerr);
    return instance;
}

void Debug::flush() const { out.flush(); }
#else
Debug::Debug() = default;

Debug::~Debug() = default;

Debug& Debug::cout() {
    static Debug instance;
    return instance;
}

Debug& Debug::cerr() {
    static Debug instance;
    return instance;
}

void Debug::flush() const {}
#endif
