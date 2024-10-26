file(GLOB TEST_SRC *.cpp)
file(GLOB CLIENT_P_SRC ClientProtocol/*.cpp)
file(GLOB SERVER_P_SRC ServerProtocol/*.cpp)

file(GLOB CLIENT_P_INC ClientProtocol/*.h)
file(GLOB SERVER_P_INC ServerProtocol/*.h)

target_include_directories(common PUBLIC "../common" "ClientProtocol" "ServerProtocol")
target_sources(DuckGameTests
        PRIVATE ${TEST_SRC} ${CLIENT_P_SRC} ${SERVER_P_SRC}
        PUBLIC  ${CLIENT_P_INC} ${SERVER_P_INC}
)