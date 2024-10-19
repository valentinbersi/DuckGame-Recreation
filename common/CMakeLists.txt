file(GLOB GAME_SRC game/*.cpp)
file(GLOB MATH_SRC math/*.cpp)
file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB SOCKET_SRC socket/*.cpp)

file(GLOB GAME_INC game/*.h)
file(GLOB MATH_INC math/*.h)
file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB SOCKET_INC socket/*.h)

target_sources(common
        PRIVATE ${GAME_SRC} ${MATH_SRC} ${PROTOCOL_SRC} ${SOCKET_SRC}
        PUBLIC ${GAME_INC} ${MATH_INC} ${PROTOCOL_INC} ${SOCKET_INC}
)
