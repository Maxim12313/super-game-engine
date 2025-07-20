#pragma once

#include <cstdint>
class GLFWwindow;

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();
    double get_width() const;
    double get_height() const;
    double get_ratio() const;
    bool should_close() const;
    void set_should_close();
    void end_drawing() const;
    int key_status(int key) const;
    void set_mouse_callback(void (*callback)(GLFWwindow *, double, double));

private:
    double m_width, m_height;
    GLFWwindow *m_window;
};
