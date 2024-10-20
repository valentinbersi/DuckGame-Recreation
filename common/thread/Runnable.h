#pragma once

/**
 * A class that represents a runnable object\n
 * Runnable class from hands-on-threads repository
 */
class Runnable {
public:
    virtual ~Runnable() = default;

    /**
     * Start the execution
     */
    virtual void start() = 0;

    /**
     * Wait for the code block to finish execution
     */
    virtual void join() = 0;

    /**
     * Stop the execution
     */
    virtual void stop() = 0;

    /**
     * Check if the execution is still running
     * @return true if the execution is still running, false otherwise
     */
    [[nodiscard]] virtual bool is_alive() const = 0;
};
