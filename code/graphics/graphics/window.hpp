#pragma once

#include <cstdint>
#include "callback_handler.hpp"

class GLFWwindow;

class Window {
public:
    Window(const Window &) = delete;
    Window(Window &&) = default;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = default;

    Window(int width, int height, const char *title);
    ~Window();
    double width() const;
    double height() const;
    double aspect_ratio() const;
    void end_drawing() const;
    bool should_close() const;
    void set_should_close();
    bool key_status(uint32_t key) const;
    void add_mouse_pos_callback(MousePosCallback callback);
    void add_key_callback(KeyCallback callback);
    void cursor_pos(double &x, double &y) const;

private:
    double m_width, m_height;
    GLFWwindow *m_window;
    CallbackHandler m_input_handler;
};
