cmake_minimum_required(VERSION 3.10)
project(dodge_master)
set(CMAKE_CXX_STANDARD 23)
set(flags "-O1 -Wall -Wextra -Wshadow -Wno-sign-compare -Wfloat-equal -fsanitize=address,undefined -Wno-switch -Wno-format")

include_directories(include objects)

add_executable(app.out main.cpp)

target_link_libraries(app.out raylib)

