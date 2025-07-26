#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Window;

class Camera {
public:
    Camera(double sensitivity);
    void move_left(float amount);
    void move_right(float amount);
    void move_forward(float amount);
    void move_backward(float amount);
    void cursor_pos_input(Window &window, double dt);
    glm::mat4 view() const;

private:
    void move_z(float amount);
    void move_x(float amount);

private:
    bool m_first_mouse;
    double m_yaw;
    double m_pitch;
    double m_prev_x; // default
    double m_prev_y; // default
    double m_sensitivity;
    double m_move_speed;
    glm::vec3 m_camera_pos;
    glm::vec3 m_camera_front;
    glm::vec3 m_camera_up;
    glm::vec3 m_camera_right;
};
