file(GLOB TEST_SRC *.cpp)
file(GLOB CLIENT_P_SRC *.cpp)
file(GLOB SERVER_P_SRC *.cpp)

file(GLOB CLIENT_P_INC *.h)
file(GLOB SERVER_P_INC *.h)

target_include_directories(common PUBLIC "../common" "ClientProtocol" "ServerProtocol")
target_sources(DuckGameTests
        PRIVATE ${TEST_SRC} ${CLIENT_P_SRC} ${SERVER_P_SRC}
        PUBLIC  ${TEST_INC} ${CLIENT_P_INC} ${SERVER_P_INC}
)
