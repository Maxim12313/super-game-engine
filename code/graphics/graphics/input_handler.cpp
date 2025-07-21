#include "input_handler.hpp"
#include <GLFW/glfw3.h>

// class public **********
void InputHandler::setup(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // let this input handler be part of the windows context
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouse_pos_runner);
    glfwSetKeyCallback(window, key_runner);
}

void InputHandler::add_mouse_pos_callback(MousePosCallback callback) {
    m_mouse_pos_callbacks.push_back(callback);
}

void InputHandler::add_key_callback(KeyCallback callback) {
    m_key_callbacks.push_back(callback);
}

// class static private **********
void InputHandler::mouse_pos_runner(GLFWwindow *window, double x, double y) {
    auto *handler =
        static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
    for (MousePosCallback callback : handler->m_mouse_pos_callbacks) {
        callback(x, y);
    }
}

void InputHandler::key_runner(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {
    auto *handler =
        static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
    for (KeyCallback callback : handler->m_key_callbacks) {
        callback(key, scancode, action, mods);
    }
}
