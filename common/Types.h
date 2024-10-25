#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

typedef const char* cppstring;
typedef char* cstring;

typedef void* Buffer;
typedef const void* ReadonlyBuffer;

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>,
          typename Alloc = std::allocator<std::pair<const Key, Value>>>
using HashMap = std::unordered_map<Key, Value, Hash, Pred, Alloc>;

template <typename... Args>
using Callable = std::function<void(Args...)>;

typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef std::int8_t i8;
typedef std::int16_t i16;
typedef std::int32_t i32;
typedef std::int64_t i64;
