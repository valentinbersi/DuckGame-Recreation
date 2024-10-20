#pragma once

#include <unordered_map>
#include <vector>

typedef const char* cppstring;
typedef char* cstring;

typedef void* Buffer;
typedef const void* ReadonlyBuffer;

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>,
          typename Alloc = std::allocator<std::pair<const Key, Value>>>
using HashMap = std::unordered_map<Key, Value, Hash, Pred, Alloc>;
