file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB COMUNICATOR_SRC comunicator/*.cpp)
file(GLOB GAME_SRC view/game/*.cpp)
file(GLOB MENU_SRC view/menu/*.cpp)

file(GLOB MENU_UI view/menu/*.ui)

file(GLOB MENU_QRSRC view/menu/*.qrc)

file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB COMUNICATOR_INC comunicator/*.h)
cmake_minimum_required(VERSION 3.13)

set(SDL2PP_WITH_IMAGE ON CACHE BOOL "" FORCE)
set(SDL2PP_WITH_TTF ON CACHE BOOL "" FORCE)
set(SDL2PP_WITH_MIXER ON CACHE BOOL "" FORCE)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2pp REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2PP_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})


file(GLOB GAME_SRC view/game/*.cpp)
file(GLOB GAME_INC view/game/*.h)

target_include_directories(common PUBLIC "../common" "protocol" "view" "comunicator")

target_sources(DuckGame
        PRIVATE ${PROTOCOL_SRC} ${GAME_SRC} ${MENU_SRC} ${MENU_UI} ${MENU_QRSRC} ${COMUNICATOR_SRC} main.cpp
        PUBLIC ${PROTOCOL_INC} ${GAME_INC} ${MENU_INC} ${COMUNICATOR_INC}
add_executable(DuckGameSDL2pp main.cpp ${GAME_SRC})

target_link_libraries(DuckGameSDL2pp ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} SDL2pp::SDL2pp)

target_include_directories(DuckGameSDL2pp
        PUBLIC ${GAME_INC}
)
