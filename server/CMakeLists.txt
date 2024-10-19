file(GLOB GAME_SRC game/*.cpp)
file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB SERVER_SRC Server.cpp)

file(GLOB GAME_INC game/*.h)
file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB SERVER_INC Server.h)

target_sources(DuckGameDedicatedServer
        PRIVATE ${GAME_SRC} ${PROTOCOL_SRC} ${SERVER_SRC} main.cpp
        PUBLIC ${GAME_INC} ${PROTOCOL_INC} ${SERVER_INC}
)
