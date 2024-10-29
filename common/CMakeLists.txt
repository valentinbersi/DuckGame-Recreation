file(GLOB EXCEPTIONS_SRC exceptions/*.cpp)
file(GLOB GAME_SRC game/*.cpp)
file(GLOB MATH_SRC math/*.cpp)
file(GLOB MESSAGES_SRC messages/*.cpp)
file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB SOCKET_SRC socket/*.cpp)
file(GLOB SYNCHRONIZED_SRC synchronized/*.cpp)
file(GLOB THREAD_SRC thread/*.cpp)
file(GLOB UTILS_SRC utils/*.cpp)

file(GLOB EXCEPTIONS_INC exceptions/*.h)
file(GLOB GAME_INC game/*.h)
file(GLOB MATH_INC math/*.h)
file(GLOB MESSAGES_INC messages/*.h)
file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB SOCKET_INC socket/*.h)
file(GLOB SYNCHRONIZED_INC synchronized/*.h)
file(GLOB THREAD_INC thread/*.h)
file(GLOB UTILS_INC utils/*.h)

target_include_directories(common PUBLIC "../common" "exceptions" "math" "messages" "protocol" "game" "socket" "utils" "thread" "synchronized")

target_sources(common
        PRIVATE ${EXCEPTIONS_SRC} ${GAME_SRC} ${MATH_SRC} ${MESSAGES_SRC} ${PROTOCOL_SRC} ${SOCKET_SRC} ${SYNCHRONIZED_SRC} ${THREAD_SRC} ${UTILS_SRC}
        PUBLIC Types.h ${EXCEPTIONS_INC} ${GAME_INC} ${MATH_INC} ${MESSAGES_INC} ${PROTOCOL_INC} ${SOCKET_INC} ${SYNCHRONIZED_INC} ${THREAD_INC} ${UTILS_INC}
)
