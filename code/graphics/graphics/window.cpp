#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "window.hpp"

void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char *title)
    : m_width(width), m_height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (m_window == nullptr) {
        throw new std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw new std::runtime_error("Failed to initialize glad");
    }

    size_callback(m_window, width, height);
}

Window::~Window() {
    if (m_window != nullptr) {
        glfwTerminate();
    }
}

double Window::get_width() const {
    return m_width;
}

double Window::get_height() const {
    return m_height;
}

double Window::get_ratio() const {
    return m_width / m_height;
}
bool Window::should_close() const {
    return glfwWindowShouldClose(m_window);
}
void Window::set_should_close() {
    glfwSetWindowShouldClose(m_window, true);
}
void Window::end_drawing() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

int Window::key_status(int key) const {
    return glfwGetKey(m_window, key);
}
