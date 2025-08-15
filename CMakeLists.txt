cmake_minimum_required(VERSION 3.10)
project(super_game_engine)

# settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON) # for ninja
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=google)

# outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# different levels
if(Build STREQUAL "R")
  message(STATUS "Configured for release")
  add_compile_options(-O3)
  add_compile_definitions(LOG_LEVEL=LOG_LEVEL_ERROR)
else()
  message(STATUS "Configured for debug")
  set(SANITIZE_FLAGS "-fsanitize=undefined")
  add_compile_options(-g -O1 -Wshadow -Wunused ${SANITIZE_FLAGS})
  add_link_options(${SANITIZE_FLAGS})
  add_compile_definitions(LOG_LEVEL=LOG_LEVEL_TRACE DEBUG)
endif()

# testing
enable_testing()

# subdirs
add_subdirectory(engine)
add_subdirectory(games)
