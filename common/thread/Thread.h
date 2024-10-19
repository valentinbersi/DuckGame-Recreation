#pragma once

#include <atomic>
#include <thread>

#include "Runnable.h"

/**
 * A class that represents an execution thread\n
 * Thread class from hands-on-threads repository
 */
class Thread: public Runnable {
    std::thread thread;

protected:
    std::atomic<bool> _keep_running;
    std::atomic<bool> _is_alive;

    /**
     * Default constructor for subclasses
     */
    Thread();

public:
    ~Thread() override = default;

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other) = delete;
    Thread& operator=(Thread&& other) = delete;

    /**
     * Start the thread
     */
    void start() final;

    /**
     * Wait for the thread to finish
     */
    void join() override;

    /**
     * Main function that will be executed by the thread
     */
    void main();

    /**
     * Stop the thread
     */
    void stop() override;

    /**
     * Check if the thread is still running
     * @return true if the thread is still running, false otherwise
     */
    [[nodiscard]] bool is_alive() const override;

    /**
     * Function that will be executed by the thread
     */
    virtual void run() = 0;
};
