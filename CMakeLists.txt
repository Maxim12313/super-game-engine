cmake_minimum_required(VERSION 3.10)
project(super_game_engine)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SANITIZE_FLAGS "-fsanitize=address")
add_link_options(${SANITIZE_FLAGS})
add_compile_options(-g -O0 -std=c++23 -Wshadow -Wunused -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG ${SANITIZE_FLAGS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCE_FILES "src/*")

find_package(spdlog REQUIRED)
find_package(raylib REQUIRED)

# add_executable(game app/dodge_master.cpp ${SOURCE_FILES})
# target_link_libraries(game raylib spdlog::spdlog)
# target_precompile_headers(game PRIVATE <pch.hpp>)

enable_testing()
file(GLOB TESTS "tests/*")
# file(GLOB TESTS "tests/view.cpp")
foreach(src IN LISTS TESTS)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src} ${SOURCE_FILES})
  add_test(NAME ${name} COMMAND ${name})
  target_link_libraries(${name} raylib spdlog::spdlog)
endforeach()
