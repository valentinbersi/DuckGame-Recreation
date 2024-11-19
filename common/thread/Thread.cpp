#include "Thread.h"

#include <iostream>

#define UNEXPECTED_EXCEPTION "Unexpected exception: "
#define UNKNOWN_EXCEPTION "Unexpected exception: <unknown>\n"

#define NEWLINE '\n'

Thread::Thread(): _keep_running(true), _is_alive(false) {}

void Thread::start() {
    _is_alive = true;
    _keep_running = true;
    thread = std::thread(&Thread::main, this);
}

void Thread::join() { thread.join(); }

bool Thread::isJoinable() const { return thread.joinable(); }

void Thread::main() {
    try {
        this->run();
    } catch (const std::exception& err) {
        std::cerr << UNEXPECTED_EXCEPTION << err.what() << NEWLINE;
    } catch (...) {
        std::cerr << UNKNOWN_EXCEPTION;
    }

    _is_alive = false;
}

void Thread::stop() { _keep_running = false; }

bool Thread::is_alive() const { return _is_alive; }
