#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/macros.hpp>
#include "context.hpp"

void init_context() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void destroy_context() {
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

GLFWwindow *create_window(int w, int h, const char *name) {
    GLFWwindow *window = glfwCreateWindow(w, h, name, nullptr, nullptr);
    if (window == nullptr)
        return nullptr;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}
