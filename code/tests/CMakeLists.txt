project(tests)

file(GLOB ecs_tests ${PROJECT_SOURCE_DIR}/ecs/*.cpp)
foreach(src IN LISTS ecs_tests)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_link_libraries(${name} PRIVATE ecs utils)
  add_test(NAME ${name} COMMAND ${name})
endforeach()

# file(GLOB graphics_tests ${PROJECT_SOURCE_DIR}/ecs/*.cpp) foreach(src IN LISTS
# ecs_tests) get_filename_component(name ${src} NAME_WE) add_executable(${name}
# ${src}) target_link_libraries(${name} PRIVATE utils g) add_test(NAME ${name}
# COMMAND ${name}) endforeach()
