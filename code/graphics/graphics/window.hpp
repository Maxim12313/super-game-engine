#pragma once

#include <cstdint>
#include <vector>
#include "input_handler.hpp"

class GLFWwindow;

class Window {
public:
    Window(const Window &) = delete;
    Window(Window &&) = default;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = default;

    Window(int width, int height, const char *title, GLFWwindow *window);
    ~Window();
    double get_width() const;
    double get_height() const;
    double get_ratio() const;
    bool should_close() const;
    void set_should_close();
    void end_drawing() const;

private:
    double m_width, m_height;
    GLFWwindow *m_window;
};
