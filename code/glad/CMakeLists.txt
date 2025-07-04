project(Glad)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_DIR}/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
