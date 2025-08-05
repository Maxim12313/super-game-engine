#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include "window.hpp"

// helpers **********
void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// class public **********
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw new std::runtime_error("Failed to initialize glad");
    }

    glfwSetFramebufferSizeCallback(m_window, size_callback);
    size_callback(m_window, width, height);
    m_input_handler.setup(m_window);
}

Window::~Window() {
    if (m_window != nullptr) {
        glfwTerminate();
    }
}

double Window::width() const {
    return m_width;
}

double Window::height() const {
    return m_height;
}

double Window::aspect_ratio() const {
    return m_width / m_height;
}
bool Window::should_close() const {
    return glfwWindowShouldClose(m_window);
}
void Window::set_should_close() {
    glfwSetWindowShouldClose(m_window, true);
}
bool Window::key_status(int key) const {
    return glfwGetKey(m_window, key);
}

bool Window::is_key_pressed(int key) const {
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void Window::end_drawing() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
void Window::add_mouse_pos_callback(MousePosCallback callback) {
    m_input_handler.add_mouse_pos_callback(callback);
}
void Window::add_key_callback(KeyCallback callback) {
    m_input_handler.add_key_callback(callback);
}

void Window::cursor_pos(double &x, double &y) const {
    glfwGetCursorPos(m_window, &x, &y);
}
