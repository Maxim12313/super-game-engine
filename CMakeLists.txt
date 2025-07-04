cmake_minimum_required(VERSION 3.10)
project(super_game_engine)

# settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON) # for ninja

# compile definition for log levels and debugging
add_compile_definitions(LOG_LEVEL=LOG_LEVEL_DEBUG DEBUG)

# outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# compilations
set(SANITIZE_FLAGS "-fsanitize=undefined")
add_link_options(${SANITIZE_FLAGS})
add_compile_options(-g -O0 -Wshadow -Wunused -Wshadow ${SANITIZE_FLAGS})

# testing
enable_testing()

# subdirs
add_subdirectory(code/utils)
add_subdirectory(code/glad)
add_subdirectory(code/ecs)
add_subdirectory(code/graphics)
