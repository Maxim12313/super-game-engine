#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include "graphics/event.hpp"
#include "graphics/window.hpp"
#include "graphics/event.hpp"
#include "../core/clock.hpp"
#include "../core/world_shader.hpp"
#include "../core/constants.hpp"
#include "graphics/camera2d.hpp"
#include "graphics/color.hpp"

// class public **********
Window::Window(int width, int height, const char *title, int target_fps)
    : m_width(width), m_height(height), m_listen_resize(false),
      m_listen_cursor_position(false), m_listen_key(false) {

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

    // register event listeners
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, resize_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetKeyCallback(m_window, key_callback);

    // initialize internal handlers
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

bool Window::toggle_listen_resize() {
    m_listen_resize = !m_listen_resize;
    return m_listen_resize;
}
bool Window::toggle_listen_cursor_position() {
    m_listen_cursor_position = !m_listen_cursor_position;
    return m_listen_cursor_position;
}
bool Window::toggle_listen_key() {
    m_listen_key = !m_listen_key;
    return m_listen_key;
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

    if (!curr->m_listen_resize)
        return;
    curr->m_events.push(resize_event(width, height));
}
void Window::cursor_position_callback(GLFWwindow *window, double x, double y) {
    Window *curr = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (!curr->m_listen_cursor_position)
        return;
    curr->m_events.push(cursor_position_event(x, y));
}
void Window::key_callback(GLFWwindow *window, int key, int scancode, int action,
                          int mods) {
    Window *curr = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (!curr->m_listen_key)
        return;
    curr->m_events.push(key_event(key, scancode, action, mods));
}
