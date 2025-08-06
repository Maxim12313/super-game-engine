#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include "graphics/window.hpp"
#include "../core/callback_handler.hpp"
#include "../core/clock.hpp"
#include "../core/shader.hpp"
#include "../core/constants.hpp"
#include "../core/drawer.hpp"
#include "../core/camera2d.hpp"
#include "graphics/color.hpp"

// helpers **********
void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// class public **********
Window::Window(int width, int height, const char *title, int target_fps)
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

    m_clock = std::make_unique<Clock>(target_fps);
    m_callback_handler = std::make_unique<CallbackHandler>(m_window);
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
    double dt = m_clock->update_dt();
    m_drawer->clear();
    return dt;
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
glm::vec2 Window::cursor_pos() const {
    glm::vec2 pos;
    glfwGetCursorPos(m_window, (double *)&pos.x, (double *)&pos.y);
    return pos;
}

// callbacks ********
void Window::add_mouse_pos_callback(MousePosCallback callback) {
    m_callback_handler->add_mouse_pos_callback(callback);
}
void Window::add_key_callback(KeyCallback callback) {
    m_callback_handler->add_key_callback(callback);
}

// clock ********
double Window::avg_fps() const {
    return m_clock->avg_fps();
}

// drawing ********
void Window::set_background(Color color) const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Window::draw_rectangle(int x, int y, int w, int h) const {
    // m_drawer->draw_rectangle(x, y, w, h, camera)
}
