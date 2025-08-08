#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include "graphics/window.hpp"
#include "../core/event.hpp"
#include "../core/clock.hpp"
#include "../core/world_shader.hpp"
#include "../core/constants.hpp"
#include "../core/drawer.hpp"
#include "graphics/camera2d.hpp"
#include "graphics/color.hpp"

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

    // for resizing
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, resize_callback);

    m_clock = std::make_unique<Clock>(target_fps);
}

Window::~Window() {
    if (m_window != nullptr) {
        glfwTerminate();
    }
}

// window dimensions *********
const int &Window::width() const {
    return m_width;
}

const int &Window::height() const {
    return m_height;
}

// game loop ********

// also returns dt
double Window::begin_update() {
    double dt = m_clock->update_dt();
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

// events ********
// TODO: switch to custom ringbuffer?
Event Window::poll_event() {
    if (m_events.empty())
        return Event{};
    Event curr = m_events.front();
    m_events.pop();
    return curr;
}

// clock ********
double Window::avg_fps() const {
    return m_clock->avg_fps();
}

// class private ********
void Window::resize_callback(GLFWwindow *window, int width, int height) {
    Window *curr = static_cast<Window *>(glfwGetWindowUserPointer(window));
    curr->m_width = width;
    curr->m_height = height;
    glViewport(0, 0, width, height);
}
