#pragma once

#include <functional>
#include <vector>

class GLFWwindow;

using MousePosCallback = std::function<void(double x, double y)>;
using KeyCallback =
    std::function<void(int key, int scancode, int action, int mods)>;

class InputHandler {
public:
    // cannot move/assign
    InputHandler(const InputHandler &) = delete;
    InputHandler(InputHandler &&) = delete;
    InputHandler &operator=(const InputHandler &) = delete;
    InputHandler &operator=(InputHandler &&) = delete;

    static InputHandler &instance();
    void add_mouse_pos_callback(MousePosCallback callback);
    void add_key_callback(KeyCallback callback);

    // must call after full init
    static void setup(GLFWwindow *window);

private:
    InputHandler() = default;
    static void mouse_pos_runner(GLFWwindow *window, double x, double y);
    static void key_runner(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

private:
    std::vector<MousePosCallback> m_mouse_pos_callbacks;
    std::vector<KeyCallback> m_key_callbacks;
};
