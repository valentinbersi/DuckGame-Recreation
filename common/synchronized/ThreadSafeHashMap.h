#pragma once
#include <mutex>

template <typename Key, typename Value, class Hash = std::hash<Key>>
class ThreadSafeMap {
    static_assert(std::is_move_assignable_v<Value> && std::is_move_constructible_v<Value>);

    HashMap<Key, Value, Hash> map;
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
};

template <typename Key, typename Value, class Hash>
ThreadSafeMap<Key, Value, Hash>::ThreadSafeMap() = default;

template <typename Key, typename Value, class Hash>
ThreadSafeMap<Key, Value, Hash>::ThreadSafeMap(const ThreadSafeMap& other) {
    std::unique_lock lck(other.mtx);
    map = other.map;
    mtx = other.mtx;
}

template <typename Key, typename Value, class Hash>
ThreadSafeMap<Key, Value, Hash>& ThreadSafeMap<Key, Value, Hash>::operator=(
        const ThreadSafeMap& other) {
    std::unique_lock lck(other.mtx);

    if (this == &other)
        return *this;

    map = other.map;
    mtx = other.mtx;
    return *this;
}

template <typename Key, typename Value, class Hash>
ThreadSafeMap<Key, Value, Hash>::ThreadSafeMap(ThreadSafeMap&& other) noexcept {
    std::unique_lock lck(other.mtx);
    map = std::move(other.map);
    mtx = std::move(other.mtx);
}

template <typename Key, typename Value, class Hash>
ThreadSafeMap<Key, Value, Hash>& ThreadSafeMap<Key, Value, Hash>::operator=(
        ThreadSafeMap&& other) noexcept {
    std::unique_lock lck(other.mtx);

    if (this == &other)
        return *this;

    map = std::move(other.map);
    mtx = std::move(other.mtx);
    return *this;
}

template <typename Key, typename Value, class Hash>
void ThreadSafeMap<Key, Value, Hash>::clear() {
    std::unique_lock lck(mtx);
    map.clear();
}

template <typename Key, typename Value, class Hash>
bool ThreadSafeMap<Key, Value, Hash>::contains(const Key& key) {
    std::unique_lock lkc(mtx);
    return map.contains(key);
}

template <typename Key, typename Value, class Hash>
bool ThreadSafeMap<Key, Value, Hash>::empty() {
    std::unique_lock lck(mtx);
    return map.empty();
}

template <typename Key, typename Value, class Hash>
void ThreadSafeMap<Key, Value, Hash>::erase(const Key& key) {
    std::unique_lock lck(mtx);
    return map.erase(key);
}

template <typename Key, typename Value, class Hash>
Value ThreadSafeMap<Key, Value, Hash>::extract(const Key& key) {
    std::unique_lock lck(mtx);
    return std::move(map.extract(key).mapped());
}

template <typename Key, typename Value, class Hash>
bool ThreadSafeMap<Key, Value, Hash>::insert(Key key, Value value) {
    std::unique_lock lck(mtx);
    return map.insert(std::make_pair(std::move(key), std::move(value))).second;
}

template <typename Key, typename Value, class Hash>
std::size_t ThreadSafeMap<Key, Value, Hash>::size() {
    std::unique_lock lck(mtx);
    return map.size();
}
