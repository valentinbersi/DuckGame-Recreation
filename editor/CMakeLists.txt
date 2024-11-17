# Collect all .cpp files recursively in the editor directory
file(GLOB_RECURSE EDITOR_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Collect all .h files recursively in the editor directory
file(GLOB_RECURSE EDITOR_INC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Collect all .ui files recursively in the editor directory
file(GLOB_RECURSE EDITOR_UI "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

# Collect all .qrc files recursively in the editor directory
file(GLOB_RECURSE EDITOR_QRC "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

# Collect all directories recursively
file(GLOB_RECURSE ALL_EDITOR_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# Filter out unique directories
set(EDITOR_DIRS "")
foreach (FILE ${ALL_EDITOR_DIRS})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND EDITOR_DIRS ${DIR})
endforeach ()
list(REMOVE_DUPLICATES EDITOR_DIRS)

# Add directories to target_include_directories
target_include_directories(DuckGameLevelEditor PUBLIC ${EDITOR_DIRS})

# Add sources to target_sources including UI and QRC files
target_sources(DuckGameLevelEditor
        PRIVATE ${EDITOR_SRC}
        PUBLIC ${EDITOR_INC}
        PRIVATE ${EDITOR_UI}
        PRIVATE ${EDITOR_QRC}
)