file(GLOB PROTOCOL_SRC protocol/*.cpp)
file(GLOB GAME_SRC view/game/*.cpp)
file(GLOB MENU_SRC view/menu/*.cpp view/menu/pages/*.cpp)

set(CMAKE_AUTOUIC ON)
file(GLOB MENU_UI view/menu/*.ui view/menu/pages/*.ui)

file(GLOB MENU_QRSRC view/menu/*.qrc)

file(GLOB PROTOCOL_INC protocol/*.h)
file(GLOB GAME_INC view/game/*.h)
file(GLOB MENU_INC view/menu/*.h view/menu/pages/*.h)

target_sources(DuckGame
        PRIVATE ${PROTOCOL_SRC} ${GAME_SRC} ${MENU_SRC} ${MENU_UI} ${MENU_QRSRC} main.cpp
        PUBLIC ${PROTOCOL_INC} ${GAME_INC} ${MENU_INC}
)

#file(GLOB PROTOCOL_SRC protocol/*.cpp)
#file(GLOB GAME_SRC view/game/*.cpp)
#file(GLOB MENU_SRC view/menu/*.cpp view/menu/pages/*.cpp)
#
#file(GLOB PROTOCOL_INC protocol/*.h)
#file(GLOB GAME_INC view/game/*.h)
#file(GLOB MENU_INC view/menu/*.h view/menu/pages/*.h)
#
#set(MENU_UI view/menu/*.ui view/menu/pages/*.ui)
#qt_wrap_ui(UI_GENERATED ${MENU_UI})
#
#set(MENU_QRSRC view/menu/*.qrc)
#qt_add_resources(QRCS_GENERATED ${MENU_QRSRC})
#
#target_sources(DuckGame
#        PRIVATE ${PROTOCOL_SRC} ${GAME_SRC} ${MENU_SRC} ${UI_GENERATED} ${QRCS_GENERATED} main.cpp
#        PUBLIC ${PROTOCOL_INC} ${GAME_INC} ${MENU_INC}
#)