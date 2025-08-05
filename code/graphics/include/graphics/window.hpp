#pragma once

#include <cstdint>
#include <functional>
#include <glm/ext/vector_float2.hpp>
#include <memory>

using MousePosCallback = std::function<void(double x, double y)>;
using KeyCallback =
    std::function<void(int key, int scancode, int action, int mods)>;

class GLFWwindow;
class CallbackHandler;
class Clock;
class ShaderManager;
class Color;

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

    // drawing
    void set_background(Color color);
    void clear_background() const;
    void draw_rectangle(glm::vec2 point, glm::vec2 dimensions, Color color);
    void draw_circle(glm::vec2 point, double radius, Color color);

private:
    double m_width, m_height;
    GLFWwindow *m_window;
    std::unique_ptr<CallbackHandler> m_input_handler;
    std::unique_ptr<Clock> m_clock;
    std::unique_ptr<ShaderManager> m_shader_manager;
};
