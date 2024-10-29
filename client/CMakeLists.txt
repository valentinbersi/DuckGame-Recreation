cmake_minimum_required(VERSION 3.13)

file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB COMUNICATOR_SRC comunicator/*.cpp)
file(GLOB GAME_SRC view/game/*.cpp)
file(GLOB MENU_SRC view/menu/*.cpp)

file(GLOB MENU_UI view/menu/*.ui)

file(GLOB MENU_QRSRC view/menu/*.qrc)

file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB COMUNICATOR_INC comunicator/*.h)
file(GLOB GAME_INC view/game/*.h)
file(GLOB MENU_INC view/menu/*.h)

target_include_directories(DuckGame PUBLIC "protocol" "view" "comunicator")

target_sources(DuckGame
        PRIVATE ${PROTOCOL_SRC} ${GAME_SRC} ${MENU_SRC} ${MENU_UI} ${MENU_QRSRC} ${COMUNICATOR_SRC} main.cpp
        PUBLIC ${PROTOCOL_INC} ${GAME_INC} ${MENU_INC} ${COMUNICATOR_INC}
)