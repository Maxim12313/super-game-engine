#include "utils/macros.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/shader.hpp>
#include <graphics/context.hpp>
#include <iostream>

int main() {
    init_context();
    GLFWwindow *window = create_window(800, 600, "reading test");
    if (window == nullptr) {
        LOG_ERROR("failed to initialize window");
        destroy_context();
        return 1;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("failed to initialize glad");
        return 1;
    }

    Shader shader("code/graphics/shaders/vertex.glsl",
                  "code/graphics/shaders/fragment.glsl");

    destroy_context();
}
