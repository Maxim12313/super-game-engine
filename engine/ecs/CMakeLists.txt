project(ecs)

# make library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
                           INTERFACE "${PROJECT_SOURCE_DIR}/include")

# link libraries
target_link_libraries(${PROJECT_NAME} INTERFACE utils)

# tests
file(GLOB tests ${PROJECT_SOURCE_DIR}/tests/*.cpp)
foreach(src IN LISTS tests)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_link_libraries(${name} PRIVATE ${PROJECT_NAME} utils)
  add_test(NAME ${name} COMMAND ${name})
endforeach()
