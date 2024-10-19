#pragma once

#include <unordered_map>
#include <vector>

typedef const char* cppstring;
typedef char* cstring;

typedef void* Buffer;
typedef const void* ReadonlyBuffer;

template <typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;
