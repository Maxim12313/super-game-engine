project(graphics)

# make library
file(GLOB_RECURSE source_files "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME}
                           PUBLIC "${PROJECT_SOURCE_DIR}/include")

# link libraries
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC OpenGL::GL Glad glfw glm::glm
  PRIVATE utils)

# tests
file(GLOB tests ${PROJECT_SOURCE_DIR}/tests/*.cpp)
foreach(src IN LISTS tests)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_link_libraries(${name} PRIVATE graphics utils)
  add_test(NAME ${name} COMMAND ${name})
endforeach()
