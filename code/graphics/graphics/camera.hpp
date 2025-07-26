#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Window;

class Camera {
public:
    Camera();
    void move_left(float amount);
    void move_right(float amount);
    void move_forward(float amount);
    void move_backward(float amount);
    void move_cursor(double x, double y, double amount);
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
    glm::vec3 m_camera_pos;
    glm::vec3 m_camera_front;
    glm::vec3 m_camera_up;
    glm::vec3 m_camera_right;
};
