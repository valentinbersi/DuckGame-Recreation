# Collect all .cpp files recursively in the server directory
file(GLOB_RECURSE SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Collect all .h files recursively in the server directory
file(GLOB_RECURSE SERVER_INC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Collect all directories recursively
file(GLOB_RECURSE ALL_SERVER_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# Filter out unique directories
set(SERVER_DIRS "")
foreach (FILE ${ALL_SERVER_DIRS})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND SERVER_DIRS ${DIR})
endforeach ()
list(REMOVE_DUPLICATES SERVER_DIRS)

# Add directories to target_include_directories
target_include_directories(DuckGameDedicatedServer PUBLIC ${SERVER_DIRS})

# Add sources to target_sources
target_sources(DuckGameDedicatedServer
        PRIVATE ${SERVER_SRC}
        PUBLIC ${SERVER_INC}
)
