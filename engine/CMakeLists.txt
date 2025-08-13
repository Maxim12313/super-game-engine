project(engine)

add_subdirectory(utils)
add_subdirectory(glad)
add_subdirectory(ecs)
add_subdirectory(graphics)
add_subdirectory(networking)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE utils graphics ecs)
