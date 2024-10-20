#pragma once
#include <functional>
#include <mutex>

#include <bits/ranges_algo.h>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>,
          typename Alloc = std::allocator<std::pair<const Key, Value>>>
class ThreadSafeMap {
    static_assert(std::is_move_assignable_v<Value> && std::is_move_constructible_v<Value>);

    HashMap<Key, Value, Hash, Pred, Alloc> map;
    std::mutex mtx;

public:
    ThreadSafeMap();
    ThreadSafeMap(const ThreadSafeMap& other);
    ThreadSafeMap& operator=(const ThreadSafeMap& other);
    ThreadSafeMap(ThreadSafeMap&& other) noexcept;
    ThreadSafeMap& operator=(ThreadSafeMap&& other) noexcept;

    /**
     * Erase all the elements of the map.
     */
    void clear();

    /**
     * Check if the map contains a key.
     * @param key the key to check
     * @return true if the map contains a key, false otherwise
     */
    bool contains(const Key& key);

    /**
     * Check if the map is empty.
     * @return true if the map is empty, false otherwise
     */
    bool empty();

    /**
     * Erase an element from the map.
     * @param key the key of the element to erase
     */
    void erase(const Key& key);

    /**
     * Extract the value paired to the given key.
     * @return the value paired to the key
     */
    Value extract(const Key& key);

    /**
     * Insert a key-value pair into the map.
     * @param key the key
     * @param value the value
     * @return true if the element was inserted, false otherwise
     */
    bool insert(Key key, Value value);

    /**
     * Get the size of the map.
     * @return the size of the map
     */
    std::size_t size();

    /**
     * Apply a function to each element of the map.
     * @param f the function to apply
     */
    void for_each(std::function<void(Value&)> f);

    /**
     * Remove elements from the map that satisfy a condition.
     * @param predicate the condition to satisfy
     */
    void remove_if(std::function<bool(Value&)> predicate);

    /**
     * Apply a function to the value paired to a key.
     * @param key the key
     * @param f the function to apply
     */
    void apply_to(const Key& key, std::function<void(Value&)> f);
};

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::ThreadSafeMap() = default;

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::ThreadSafeMap(const ThreadSafeMap& other) {
    std::unique_lock lck(other.mtx);
    map = other.map;
    mtx = other.mtx;
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
ThreadSafeMap<Key, Value, Hash, Pred, Alloc>&
        ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::operator=(const ThreadSafeMap& other) {
    std::unique_lock lck(other.mtx);

    if (this == &other)
        return *this;

    map = other.map;
    mtx = other.mtx;
    return *this;
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::ThreadSafeMap(ThreadSafeMap&& other) noexcept {
    std::unique_lock lck(other.mtx);
    map = std::move(other.map);
    mtx = std::move(other.mtx);
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
ThreadSafeMap<Key, Value, Hash, Pred, Alloc>&
        ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::operator=(ThreadSafeMap&& other) noexcept {
    std::unique_lock lck(other.mtx);

    if (this == &other)
        return *this;

    map = std::move(other.map);
    mtx = std::move(other.mtx);
    return *this;
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
void ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::clear() {
    std::unique_lock lck(mtx);
    map.clear();
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
bool ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::contains(const Key& key) {
    std::unique_lock lkc(mtx);
    return map.contains(key);
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
bool ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::empty() {
    std::unique_lock lck(mtx);
    return map.empty();
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
void ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::erase(const Key& key) {
    std::unique_lock lck(mtx);
    return map.erase(key);
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
Value ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::extract(const Key& key) {
    std::unique_lock lck(mtx);
    return std::move(map.extract(key).mapped());
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
bool ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::insert(Key key, Value value) {
    std::unique_lock lck(mtx);
    return map.insert(std::make_pair(std::move(key), std::move(value))).second;
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
std::size_t ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::size() {
    std::unique_lock lck(mtx);
    return map.size();
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
void ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::for_each(std::function<void(Value&)> f) {
    std::unique_lock lck(mtx);
    std::ranges::for_each(map, f);
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
void ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::remove_if(
        std::function<bool(Value&)> predicate) {
    std::unique_lock lck(mtx);
    std::ranges::remove_if(map, predicate);
}

template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
void ThreadSafeMap<Key, Value, Hash, Pred, Alloc>::apply_to(const Key& key,
                                                            std::function<void(Value&)> f) {
    std::unique_lock lck(mtx);
    f(map.at(key));
}
