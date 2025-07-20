#pragma once
#include "graphics/input_handler.hpp"
#include "graphics/window.hpp"

class Controller {
public:
    Controller(Window window, InputHandler &input_handler);

private:
    Window m_window;
    InputHandler &m_input_handler;
};

Controller Controller_setup();
