#pragma once

#include <cstdint>
#include <functional>
#include <memory>

class GLFWwindow;
using MousePosCallback = std::function<void(double x, double y)>;
using KeyCallback =
    std::function<void(int key, int scancode, int action, int mods)>;
class CallbackHandler;

class Clock;

class Window {
public:
    Window(const Window &) = delete;
    Window(Window &&) = default;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = default;

    Window(int width = 1280, int height = 720,
           const char *title = "my cool game", int target_fps = 60);
    ~Window();

    // window dimensions
    double width() const;
    double height() const;
    double aspect_ratio() const;

    // game loop
    double begin_update();
    void end_update();
    bool should_close() const;
    void set_should_close();

    // input
    bool key_status(int key) const;
    bool is_key_pressed(int key) const;
    void cursor_pos(double &x, double &y) const;

    // callbacks
    void add_mouse_pos_callback(MousePosCallback callback);
    void add_key_callback(KeyCallback callback);

    // clock
    double avg_fps() const;

private:
    double m_width, m_height;
    GLFWwindow *m_window;
    std::unique_ptr<CallbackHandler> m_input_handler;
    std::unique_ptr<Clock> m_clock;
};
