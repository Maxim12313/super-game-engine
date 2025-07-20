#include "input_handler.hpp"
#include <GLFW/glfw3.h>

// class public **********

InputHandler &InputHandler::instance() {
    static InputHandler handler;
    return handler;
}

void InputHandler::add_mouse_pos_callback(MousePosCallback callback) {
    m_mouse_pos_callbacks.push_back(callback);
}

void InputHandler::add_key_callback(KeyCallback callback) {
    m_key_callbacks.push_back(callback);
}

void InputHandler::setup(GLFWwindow *window) {
    // settings
    instance();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_pos_runner);
    glfwSetKeyCallback(window, key_runner);
}

// class private **********

void InputHandler::mouse_pos_runner(GLFWwindow *window, double x, double y) {
    InputHandler &handler = instance();
    for (MousePosCallback callback : handler.m_mouse_pos_callbacks) {
        callback(x, y);
    }
}

void InputHandler::key_runner(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {
    InputHandler &handler = instance();
    for (KeyCallback callback : handler.m_key_callbacks) {
        callback(key, scancode, action, mods);
    }
}
