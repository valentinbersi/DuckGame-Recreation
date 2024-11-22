cmake_minimum_required(VERSION 3.13)

add_compile_options(-Wno-error=zero-as-null-pointer-constant -Wno-error=deprecated-declarations)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif ()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif ()

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
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

include(FetchContent)

# Define target: lib common between client, server and editor programs
add_library(common STATIC)

# add the source files that make the lib
add_subdirectory(common/)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.6.3
)

FetchContent_MakeAvailable(yaml-cpp)

add_dependencies(common yaml-cpp)
target_link_libraries(common PUBLIC yaml-cpp)

# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(common ${MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(common PUBLIC .)

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/assets)
file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/maps)
file(COPY ${CMAKE_SOURCE_DIR}/maps/ DESTINATION ${CMAKE_BINARY_DIR}/maps)

# Install libSDL2pp (for client or editor)
if (CLIENT OR EDITOR)
    #add_custom_command(
    #        OUTPUT ${CMAKE_BINARY_DIR}/graphics.stamp
    #        COMMAND ${CMAKE_COMMAND} -E env bash ${CMAKE_SOURCE_DIR}/install_graphics.sh
    #        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/graphics.stamp
    #)

    add_custom_target(graphics ALL DEPENDS ${CMAKE_BINARY_DIR}/graphics.stamp)

    FetchContent_Declare(
            sdl2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.30.9
    )

    FetchContent_MakeAvailable(sdl2)

    FetchContent_Declare(
            opus
            GIT_REPOSITORY https://github.com/xiph/opus.git
            GIT_TAG v1.5.2
    )

    FetchContent_MakeAvailable(opus)

    FetchContent_Declare(
            opusfile
            GIT_REPOSITORY https://github.com/xiph/opusfile.git
            GIT_BRANCH master
    )

    FetchContent_MakeAvailable(opusfile)

    FetchContent_Declare(
            sdl2-mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.0
    )

    FetchContent_MakeAvailable(sdl2-mixer)

    FetchContent_Declare(
            sdl2-ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.22.0
    )

    FetchContent_MakeAvailable(sdl2-ttf)

    FetchContent_Declare(
            sdl2-image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-2.8.2
    )

    FetchContent_MakeAvailable(sdl2-image)

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
    add_dependencies(DuckGame graphics common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

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
    add_dependencies(DuckGameLevelEditor graphics common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui)

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
