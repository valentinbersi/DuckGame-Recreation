file(GLOB CONTROLLER_SRC controller/*.cpp)
file(GLOB MODEL_SRC model/*.cpp)
file(GLOB VIEW_SRC view/*.cpp)

file(GLOB CONTROLLER_INC controller/*.h)
file(GLOB MODEL_INC model/*.cpp)
file(GLOB VIEW_INC view/*.cpp)

target_sources(DuckGameLevelEditor
        PRIVATE ${CONTROLLER_SRC} ${MODEL_SRC} ${VIEW_SRC} main.cpp
        PUBLIC ${CONTROLLER_INC} ${MODEL_INC} ${VIEW_INC}
)
