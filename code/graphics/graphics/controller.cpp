#include "controller.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/constants.hpp"
#include "window.hpp"

Controller::Controller(Window window, InputHandler &input_handler)
    : m_window(std::move(window)), m_input_handler(input_handler) {
}

Controller Controller_setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = window::WIDTH;
    int height = window::HEIGHT;
    const char *title = window::TITLE;

    GLFWwindow *window =
        glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        throw new std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw new std::runtime_error("Failed to initialize glad");
    }

    Window game_window = Window(width, height, title, window);
    InputHandler &input_handler = InputHandler::instance();

    return Controller{game_window, input_handler};
}
