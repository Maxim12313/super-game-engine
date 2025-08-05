#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Window;

enum class Direction { UP, RIGHT, FORWARD, DOWN, LEFT, BACKWARD };

class Camera {
public:
    Camera(double fov, double z_near, double z_far);
    void move_direction(Direction dir, double amount);
    void move_cursor(double x, double y, double amount);

    void change_fov(double amount);
    glm::mat4 view() const;
    glm::mat4 projection(double aspect_ratio) const;

private:
    void move_z(float amount);
    void move_x(float amount);
    void move_y(float amount);

private:
    bool m_first_mouse;
    double m_yaw;
    double m_pitch;
    double m_prev_x; // default
    double m_prev_y; // default
    double m_fov;
    double m_z_near;
    double m_z_far;
    glm::vec3 m_camera_pos;
    glm::vec3 m_camera_front;
    glm::vec3 m_camera_up;
    glm::vec3 m_camera_right;
};
