cmake_minimum_required(VERSION 3.10)
project(dodge_master)
set(CMAKE_CXX_STANDARD 23)

set(flaags "-g -O0 -Wall -Wextra -Wshadow -Wno-sign-compare -Wfloat-equal
    -fsanitize=address,undefined -Wno-switch -Wno-format")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCE_FILES "src/*")

add_executable(game app/dodge_master.cpp ${SOURCE_FILES})
target_link_libraries(game raylib)

enable_testing()
file(GLOB TESTS "tests/*")
foreach(src IN LISTS TESTS)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src} ${SOURCE_FILES})
  add_test(NAME ${name} COMMAND ${name})
  target_link_libraries(${name} raylib)
endforeach()
