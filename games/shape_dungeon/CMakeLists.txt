project(shape_dungeon)

file(GLOB_RECURSE source_files "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(project_lib ${PROJECT_NAME}_lib)

add_library(${project_lib} ${source_files})
target_link_libraries(${project_lib} PUBLIC engine)
target_include_directories(${project_lib} PUBLIC "${PROJECT_SOURCE_DIR}/src")

file(GLOB tests ${PROJECT_SOURCE_DIR}/tests/*.cpp)
foreach(src IN LISTS tests)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_link_libraries(${name} PRIVATE ${project_lib} utils)
  add_test(NAME ${name} COMMAND ${name})
endforeach()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${project_lib})
