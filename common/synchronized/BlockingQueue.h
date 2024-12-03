#pragma once

#include <climits>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>
#include <utility>

struct ClosedQueue final: std::runtime_error {
    /**
     * Construct a ClosedQueue exception.
     */
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

/**
 * A thread-safe queue with a maximum size.\n
 * Based on hands-on-threads Queue class
 * @tparam T The type the Queue holds
 * @tparam C The underlying container used in the queue. @code std::deque@endcode by default.
 */
template <typename T, class C = std::deque<T>>
class BlockingQueue final {
    static_assert(std::is_move_assignable_v<T> && std::is_move_constructible_v<T>);

    std::queue<T, C> q;
    const std::uint32_t max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    ~BlockingQueue() = default;
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;
    BlockingQueue(const BlockingQueue&&) = delete;
    BlockingQueue& operator=(const BlockingQueue&&) = delete;

    /**
     * Construct a queue with maximum size UINT_MAX - 1.
     */
    BlockingQueue();

    /**
     * Construct a queue with a maximun size.
     * @param max_size The maximum size of the queue.
     */
    explicit BlockingQueue(std::uint32_t max_size);

    /**
     * Try to push a value to the queue.\n
     * Non-Blocking operation.\n
     * If the value is pushed, notifies all threads waiting for the queue to not be empty.
     * @param val The value to push.
     * @return @code true@endcode if the value was pushed, @code false@endcode otherwise.
     * @throw ClosedQueue If the queue is closed.
     */
    bool try_push(const T& val);

    /**
     * Try to push a value to the queue.\n
     * Non-Blocking operation.\n
     * Notifies all threads waiting for the queue to not be empty.
     * @param val The value to push.
     * @return @code true@endcode if the value was pushed, @code false@endcode otherwise.
     * @throw ClosedQueue If the queue is closed
     */
    bool try_push(T&& val);

    /**
     * Try to pop a value from the queue.\n
     * Non-Blocking operation.\n
     * Notifies all threads waiting for the queue to not be full.
     * @return The value if the queue is not empty, @code std::nullopt@endcode otherwise.
     * @throw ClosedQueue If the queue is not empty.
     */
    std::optional<T> try_pop();

    /**
     * Push a value to the queue.\n
     * Blocking operation.\n
     * Notifies all threads waiting for the queue to not be empty.
     * @param val The value to push.
     * @throw ClosedQueue If the queue is closed.
     */
    void push(const T& val);

    /**
     * Push a value to the queue.\n
     * Blocking operation.\n
     * Notifies all threads waiting for the queue to not be empty.
     * @param val The value to push.
     * @throw ClosedQueue If the queue if closed
     */
    void push(T&& val);

    /**
     * Pop a value from the queue.\n
     * Blocking operation.\n
     * Notifies all threads waiting for the queue to not be full.
     * @return The poped value
     * @throw ClosedQueue if the queue is closed
     */
    T pop();

    /**
     * Close the queue. All threads waiting for the queue will be unblocked.
     * @throw std::runtime_error If the queue is already closed.
     */
    void close();

    /**
     * Get a queue with all the elements of the blocking queue
     * @return a queue with all the elements of the blocking queue
     */
    std::queue<T, C> popAll();

    /**
     * Get a elements acording to the size of the queue
     * @param func the function taht dictates the amount of
     * elements to pop.
     * @return the element poped last of the amount or nullopt if the queue is empty
     */
    std::optional<T> tryPopPercent(std::function<int(int)> func);
};

template <typename T, class C>
std::queue<T, C> BlockingQueue<T, C>::popAll() {
    std::unique_lock lck(mtx);
    return std::move(q);
}
template <typename T, class C>
std::optional<T> BlockingQueue<T, C>::tryPopPercent(std::function<int(int)> func) {
    std::unique_lock lck(mtx);
    if (q.empty()) {
        if (closed)
            throw ClosedQueue();
        return std::nullopt;
    }
    if (q.size() == this->max_size)
        is_not_full.notify_all();

    int amount = func(q.size());
    for (int i = 0; i < amount - 1; i++) {
        q.pop();
    }
    T val(std::move(q.front()));
    q.pop();
    return val;
}

template <typename T, class C>
BlockingQueue<T, C>::BlockingQueue(): max_size(UINT_MAX - 1), closed(false) {}

template <typename T, class C>
BlockingQueue<T, C>::BlockingQueue(const std::uint32_t max_size):
        max_size(max_size), closed(false) {}

template <typename T, class C>
bool BlockingQueue<T, C>::try_push(T const& val) {
    std::unique_lock lck(mtx);

    if (closed)
        throw ClosedQueue();

    if (q.size() == this->max_size)
        return false;

    if (q.empty())
        is_not_empty.notify_all();

    q.push(val);
    return true;
}

template <typename T, class C>
bool BlockingQueue<T, C>::try_push(T&& val) {
    std::unique_lock lck(mtx);

    if (closed)
        throw ClosedQueue();

    if (q.size() == this->max_size)
        return false;

    if (q.empty())
        is_not_empty.notify_all();

    q.push(std::move(val));
    return true;
}

template <typename T, class C>
std::optional<T> BlockingQueue<T, C>::try_pop() {
    std::unique_lock lck(mtx);

    if (q.empty()) {
        if (closed)
            throw ClosedQueue();

        return std::nullopt;
    }

    if (q.size() == this->max_size)
        is_not_full.notify_all();

    T val(std::move(q.front()));
    q.pop();
    return val;
}

template <typename T, class C>
void BlockingQueue<T, C>::push(T const& val) {
    std::unique_lock lck(mtx);

    if (closed)
        throw ClosedQueue();

    while (q.size() == this->max_size) is_not_full.wait(lck);

    if (q.empty())
        is_not_empty.notify_all();

    q.push(val);
}

template <typename T, class C>
void BlockingQueue<T, C>::push(T&& val) {
    std::unique_lock lck(mtx);

    if (closed)
        throw ClosedQueue();

    while (q.size() == this->max_size) is_not_full.wait(lck);

    if (q.empty())
        is_not_empty.notify_all();

    q.push(std::move(val));
}

template <typename T, class C>
T BlockingQueue<T, C>::pop() {
    std::unique_lock lck(mtx);

    while (q.empty()) {
        if (closed)
            throw ClosedQueue();

        is_not_empty.wait(lck);
    }

    if (q.size() == this->max_size)
        is_not_full.notify_all();

    T val(std::move(q.front()));
    q.pop();
    return val;
}

template <typename T, class C>
void BlockingQueue<T, C>::close() {
    std::unique_lock lck(mtx);

    if (closed)
        throw std::runtime_error("The queue is already closed.");

    closed = true;
    is_not_empty.notify_all();
}
