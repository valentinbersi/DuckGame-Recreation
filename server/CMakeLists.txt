file(GLOB GAME_SRC game/*.cpp)
file(GLOB GAME_OBJECTS_SRC game/objects/*.cpp)
file(GLOB GAME_PLAYER_SRC game/player/*.cpp)
file(GLOB GAME_INPUT_SRC game/input/*.cpp)
file(GLOB GAME_EVENT_SRC game/event/*.cpp)
file(GLOB GAME_RECORDS_SRC game/records/*.cpp)
file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB REF_COUNTED_SRC refCounted/*.cpp)
file(GLOB THREADS_SRC threads/*.cpp)
file(GLOB SERVER_SRC Server.cpp)
file(GLOB COMMANDS_SRC commands/*.cpp)
file(GLOB VCLIENT_SRC client/*.cpp)
file(GLOB SYNC_SRC synchronized/*.cpp)


file(GLOB GAME_INC game/*.h)
file(GLOB GAME_OBJECTS_INC game/objects/*.h)
file(GLOB GAME_PLAYER_INC game/player/*.h)
file(GLOB GAME_INPUT_INC game/player/*.h)
file(GLOB GAME_EVENT_INC game/event/*.h)
file(GLOB GAME_RECORDS_INC game/records/*.h)
file(GLOB THREADS_INC threads/*.h)
file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB REF_COUNTED_INC refCounted/*.h)
file(GLOB SERVER_INC Server.h)
file(GLOB COMMANDS_INC commands/*.h)
file(GLOB VCLIENT_INC client/*.h)
file(GLOB SYNC_INC synchronized/*.h)

target_include_directories(DuckGameDedicatedServer PUBLIC "game" "game/objects" "game/player" "game/input" "protocol" "game/event" "game/records" "commands" "client" "threads" "synchronized" "refCounted")

target_sources(DuckGameDedicatedServer
        PRIVATE ${GAME_SRC} ${GAME_OBJECTS_SRC} ${GAME_PLAYER_SRC} ${GAME_INPUT_SRC} ${GAME_EVENT_SRC} ${GAME_RECORDS_SRC} ${PROTOCOL_SRC} ${REF_COUNTED_SRC} ${SERVER_SRC} ${COMMANDS_SRC} ${VCLIENT_SRC} ${THREADS_SRC} ${SYNC_SRC} main.cpp
        PUBLIC ${GAME_INC} ${GAME_OBJECTS_INC} ${GAME_PLAYER_INC} ${GAME_INPUT_INC} ${GAME_EVENT_INC} ${GAME_RECORDS_INC} ${PROTOCOL_INC} ${REF_COUNTED_INC} ${SERVER_INC} ${COMMANDS_INC} ${VCLIENT_INC} ${THREADS_INC} ${SYNC_INC}
)
