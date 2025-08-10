#pragma once

#include <cstdint>
#include <functional>
#include <glm/ext/vector_float2.hpp>
#include <memory>
#include "event.hpp"
#include <queue>

using MousePosCallback = std::function<void(double x, double y)>;
using KeyCallback =
    std::function<void(int key, int scancode, int action, int mods)>;

class GLFWwindow;
class Clock;
enum class Direction;

class Window {
public:
    Window(int width = 1280, int height = 720,
           const char *title = "my cool game", int target_fps = 60);
    ~Window();

    // window dimensions
    const int &width() const;
    const int &height() const;

    // game loop
    double begin_update();
    void end_update();
    bool should_close() const;
    void set_should_close();

    // input
    bool key_status(int key) const;
    bool is_key_pressed(int key) const;
    glm::vec2 cursor_pos() const;

    // events
    // returns event with EventType::None if none
    Event poll_event();
    bool toggle_listen_resize();
    bool toggle_listen_cursor_position();
    bool toggle_listen_key();

    // clock
    double avg_fps() const;

private:
    static void resize_callback(GLFWwindow *window, int width, int height);
    static void cursor_position_callback(GLFWwindow *window, double x,
                                         double y);
    static void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);

private:
    int m_width;
    int m_height;
    bool m_listen_resize;
    bool m_listen_cursor_position;
    bool m_listen_key;
    GLFWwindow *m_window;
    std::unique_ptr<Clock> m_clock;
    std::queue<Event> m_events;
};
