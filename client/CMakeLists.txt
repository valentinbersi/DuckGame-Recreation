# Collect all .cpp files recursively in the server directory
file(GLOB_RECURSE CLIENT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Collect all .h files recursively in the server directory
file(GLOB_RECURSE CLIENT_INC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Collect all .ui files recursively in the server directory
file(GLOB_RECURSE CLIENT_UI "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

# Collect all .qrc files recursively in the server directory
file(GLOB_RECURSE CLIENT_QRC "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

# Collect all directories recursively
file(GLOB_RECURSE ALL_CLIENT_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# Filter out unique directories
set(CLIENT_DIRS "")
foreach (FILE ${ALL_CLIENT_DIRS})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND CLIENT_DIRS ${DIR})
endforeach ()
list(REMOVE_DUPLICATES CLIENT_DIRS)

# Add directories to target_include_directories
target_include_directories(DuckGame PUBLIC ${CLIENT_DIRS})

# Add sources to target_sources including UI and QRC files
target_sources(DuckGame
        PRIVATE ${CLIENT_SRC}
        PUBLIC ${CLIENT_INC}
        PRIVATE ${CLIENT_UI}
        PRIVATE ${CLIENT_QRC}
)