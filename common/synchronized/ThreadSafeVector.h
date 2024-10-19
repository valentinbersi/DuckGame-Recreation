#pragma once

#include <functional>
#include <mutex>
#include <stdexcept>
#include <utility>
#include <vector>

/**
 * A thread-safe vector that allows multiple threads to access it concurrently without generating
 * race conditions. It's also move safe, meaning that objects won't be moved in memory.
 * @tparam T The type of the elements in the vector
 */
template <typename T>
class ThreadSafeVector {
    static constexpr auto ERASE_FAIL = "Can't erase from an empty vector";
    static constexpr auto ACCESS_FAIL = "index is out of bounds";
    static constexpr auto BAD_RANGE = "start cannot be bigger or equal than end";
    static constexpr auto BAD_START = "start is out of bounds";
    static constexpr auto BAD_END = "end is out of bounds";

    std::vector<T> container;
    std::mutex m;

public:
    ThreadSafeVector() = default;
    ~ThreadSafeVector() = default;

    /**
     * Adds a copy of the given element at the end of the vector.
     * @param elem The element to be added.
     */
    void push_back(const T& elem);

    /**
     * Takes ownership of the given element and adds it at the end of the vector.
     * @param elem The element to be added
     */
    void push_back(T&& elem);

    /**
     * Constructs an element of type @code T@endcode in place at the end of the vector.
     * @tparam Args The types of the arguments to be passed to the constructor of @code T@endcode
     * @param args The arguments to be passed to the constructor of @code T@endcode
     */
    template <typename... Args>
    void emplace_back(Args&&... args);

    /**
     * Erases the element in the given position
     * @param position The position of the element to be erased
     */
    void erase(size_t position);

    /**
     * Get a copy of the element in the given position.\n
     * std::vector operator[] returns a reference, here a reference can't be returned because
     * other thread could erase the element being referenced
     * @param index The position of the element to be accessed
     * @return A copy of the element in the given position
     */
    [[nodiscard]] T operator[](size_t index) const;

    /**
     * Get the amount of elements in the vector
     * @return The amount of elements in the vector
     */
    [[nodiscard]] size_t size() const;

    /**
     * Check if the vector is empty
     * @return @code true@endcode if the vector is empty, @code false@endcode otherwise
     */
    [[nodiscard]] bool empty() const;

    /**
     * Apply a function to each element in the vector
     * @param f The function to be applied.
     */
    void for_each(const std::function<void(T&)>& f);

    /**
     * Apply a function to each element in the vector that satisfies the given predicate
     * @param f The function to be applied
     * @param predicate The predicate to be satisfied
     */
    void for_each_if(const std::function<void(T&)>& f, const std::function<bool(T&)>& predicate);

    /**
     * Moves all the elements that satisfy the given predicate into the returned vector
     * @param predicate The predicate to be satisfied
     * @return An array containing the removed elements
     */
    void remove_if(const std::function<bool(T&)>& predicate);

    /**
     * Apply a function to each element in the given range
     * @param f The function to be applied
     * @param start The start of the range (inclusive)
     * @param end The end of the range (exclusive)
     */
    void for_range(std::function<void(T&)> f, size_t start, size_t end);
};

template <typename T>
void ThreadSafeVector<T>::push_back(const T& elem) {
    std::lock_guard lock(m);
    container.push_back(elem);
}

template <typename T>
void ThreadSafeVector<T>::push_back(T&& elem) {
    std::lock_guard lock(m);
    container.push_back(std::move(elem));
}

template <typename T>
template <typename... Args>
void ThreadSafeVector<T>::emplace_back(Args&&... args) {
    std::lock_guard lock(m);
    container.emplace_back(args...);
}

template <typename T>
void ThreadSafeVector<T>::erase(size_t position) {
    std::lock_guard lock(m);

    if (empty())
        throw std::logic_error(ERASE_FAIL);

    container.erase(position);
}

template <typename T>
T ThreadSafeVector<T>::operator[](size_t index) const {
    std::lock_guard lock(m);

    if (index >= container.size())
        throw std::out_of_range(ACCESS_FAIL);

    return container[index];
}

template <typename T>
size_t ThreadSafeVector<T>::size() const {
    std::lock_guard lock(m);
    return container.size();
}

template <typename T>
bool ThreadSafeVector<T>::empty() const {
    std::lock_guard lock(m);
    return container.empty();
}

template <typename T>
void ThreadSafeVector<T>::for_each(const std::function<void(T&)>& f) {
    std::lock_guard lock(m);
    std::for_each(container.begin(), container.end(), f);
}

template <typename T>
void ThreadSafeVector<T>::for_each_if(const std::function<void(T&)>& f,
                                      const std::function<bool(T&)>& predicate) {
    std::lock_guard lock(m);
    std::for_each(container.begin(), container.end(), [&predicate, &f](T& elem) {
        if (predicate(elem))
            f(elem);
    });
}

template <typename T>
void ThreadSafeVector<T>::remove_if(const std::function<bool(T&)>& predicate) {
    std::lock_guard lock(m);

    auto i = container.begin();
    while (i != container.end()) {
        if (predicate(*i))
            i = container.erase(i);
        else
            ++i;
    }
}

template <typename T>
void ThreadSafeVector<T>::for_range(std::function<void(T&)> f, size_t start, const size_t end) {
    std::lock_guard lock(m);
    if (start >= end)
        throw std::invalid_argument(BAD_RANGE);

    if (start >= container.size())
        throw std::range_error(BAD_START);

    if (end > container.size())
        throw std::range_error(BAD_END);

    std::for_each_n(container.begin() + start, end - start, f);
}
