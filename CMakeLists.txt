cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif ()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif ()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

project(DuckGame
        VERSION 1.0
        HOMEPAGE_URL "https://github.com/valentinbersi/TP_DuckGame_Grupo08"
        LANGUAGES CXX
)

# Posix standard 2008
add_definitions(-D_POSIX_C_SOURCE=200809L)

option(TESTS "Enable / disable tests." ON)
option(CLIENT "Enable / disable client program." ON)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." ON)
option(MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
add_library(common STATIC)

# add the source files that make the lib
add_subdirectory(common/)


# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(common ${MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(common PUBLIC .)

# Install libSDL2pp (for client or editor)
if (CLIENT OR EDITOR)
    include(FetchContent)
    FetchContent_Declare(
            libSDL2pp
            URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    set(SDL2PP_WITH_IMAGE ON CACHE BOOL "" FORCE)
    set(SDL2PP_WITH_TTF ON CACHE BOOL "" FORCE)
    set(SDL2PP_WITH_MIXER ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(libSDL2pp)

    include(GNUInstallDirs)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt5 COMPONENTS Core Gui Widgets)

    target_include_directories(common PUBLIC ${Qt5_SOURCE_DIR})
endif ()

# Program section
# ---------------
if (CLIENT)
    add_executable(DuckGame)

    # Make them depend on taller_common lib
    add_dependencies(DuckGame common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

    # Add source files and enable warnings
    add_subdirectory(client)

    set_project_warnings(DuckGame ${MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(DuckGame PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(DuckGame common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

    install(TARGETS DuckGame
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif ()

if (SERVER)
    add_executable(DuckGameDedicatedServer)

    # Make them depend on taller_common lib
    add_dependencies(DuckGameDedicatedServer common)

    # Add source files and enable warnings
    add_subdirectory(server)

    set_project_warnings(DuckGameDedicatedServer ${MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the taller_common lib target
    target_link_libraries(DuckGameDedicatedServer common)
endif ()

if (EDITOR)
    add_executable(DuckGameLevelEditor)

    # Make them depend on taller_common lib
    add_dependencies(DuckGameLevelEditor common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

    # Add source files and enable warnings
    add_subdirectory(editor)

    set_project_warnings(DuckGameLevelEditor ${MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(DuckGameLevelEditor PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(DuckGameLevelEditor common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

    install(TARGETS DuckGameLevelEditor
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif ()


# Testing section
# ---------------

if (TESTS)
    set(CMAKE_BUILD_TYPE Debug)
    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    # target for testing
    add_executable(DuckGameTests)

    # Change this if you have to.
    add_dependencies(DuckGameTests common)

    # Say where to find the xoz headers
    target_include_directories(DuckGameTests PUBLIC .)

    # Add the source files to the taller_tests target
    add_subdirectory(tests/)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(DuckGameTests ${MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Say where googletest headers can be found
    target_include_directories(DuckGameTests
            PUBLIC
            ${gtest_SOURCE_DIR}/include
            ${gmock_SOURCE_DIR}/include
    )

    # Change this if you have to.
    target_link_libraries(DuckGameTests
            common
            GTest::gtest_main
    )
endif ()
