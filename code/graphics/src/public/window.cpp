#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include "graphics/window.hpp"
#include "../core/callback_handler.hpp"
#include "../core/clock.hpp"

// helpers **********
void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// class public **********
Window::Window(int width, int height, const char *title, int target_fps)
    : m_width(width), m_height(height),
      m_input_handler(std::make_unique<CallbackHandler>()),
      m_clock(std::make_unique<Clock>(target_fps)) {

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
    m_input_handler->setup(m_window);
}

Window::~Window() {
    if (m_window != nullptr) {
        glfwTerminate();
    }
}

// window dimensions *********
double Window::width() const {
    return m_width;
}

double Window::height() const {
    return m_height;
}

double Window::aspect_ratio() const {
    return m_width / m_height;
}

// game loop ********

// also returns dt
double Window::begin_update() {
    return m_clock->update_dt();
}

void Window::end_update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_clock->adjust_fps();
}
bool Window::should_close() const {
    return glfwWindowShouldClose(m_window);
}
void Window::set_should_close() {
    glfwSetWindowShouldClose(m_window, true);
}

// input ********
bool Window::key_status(int key) const {
    return glfwGetKey(m_window, key);
}

bool Window::is_key_pressed(int key) const {
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}
void Window::cursor_pos(double &x, double &y) const {
    glfwGetCursorPos(m_window, &x, &y);
}

// callbacks ********
void Window::add_mouse_pos_callback(MousePosCallback callback) {
    m_input_handler->add_mouse_pos_callback(callback);
}
void Window::add_key_callback(KeyCallback callback) {
    m_input_handler->add_key_callback(callback);
}

// clock ********
double Window::avg_fps() const {
    return m_clock->avg_fps();
}
