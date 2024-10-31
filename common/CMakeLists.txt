# Collect all .cpp files recursively in the server directory
file(GLOB_RECURSE COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Collect all .h files recursively in the server directory
file(GLOB_RECURSE COMMON_INC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Collect all directories recursively
file(GLOB_RECURSE ALL_COMMON_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# Filter out unique directories
set(COMMON_DIRS "")
foreach (FILE ${ALL_COMMON_DIRS})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND COMMON_DIRS ${DIR})
endforeach ()
list(REMOVE_DUPLICATES COMMON_DIRS)

# Add directories to target_include_directories
target_include_directories(common PUBLIC ${COMMON_DIRS})

# Add sources to target_sources
target_sources(common
        PRIVATE ${COMMON_SRC}
        PUBLIC ${COMMON_INC}
)
