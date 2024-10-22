file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB GAME_SRC view/game/*.cpp)
file(GLOB MENU_SRC view/menu/*.cpp)

file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB GAME_INC view/game/*.h)
file(GLOB MENU_INC view/menu/*.h)

target_include_directories(common PUBLIC "../common" "protocol" "view")

target_sources(DuckGame
        PRIVATE ${PROTOCOL_SRC} ${GAME_SRC} ${MENU_SRC} main.cpp
        PUBLIC ${PROTOCOL_INC} ${GAME_INC} ${MENU_INC}
)
