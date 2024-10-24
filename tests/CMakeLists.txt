file(GLOB TEST_SRC *.cpp)
file(GLOB TEST_INC *.h)

target_include_directories(common PUBLIC "../common" "../client" "../server")
target_sources(DuckGameTests
        PRIVATE ${TEST_SRC}
        PUBLIC  ${TEST_INC}
)
