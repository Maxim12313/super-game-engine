project(ecs)

# find files
file(GLOB_RECURSE source_files "${PROJECT_SOURCE_DIR}/*.cpp")
add_library(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE utils)
