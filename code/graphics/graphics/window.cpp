#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "window.hpp"

// helpers **********
void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// class public **********
Window::Window(int width, int height, const char *title, GLFWwindow *window)
    : m_width(width), m_height(height) {
    glfwSetFramebufferSizeCallback(m_window, size_callback);
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
