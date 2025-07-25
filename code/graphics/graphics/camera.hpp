#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Window;

class Camera {
public:
    Camera();
    void handle_input(Window &window, double dt);
    glm::mat4 view() const;

private:
    bool m_first_mouse;
    double m_yaw;
    double m_pitch;
    double m_prev_x;
    double m_prev_y;
    glm::vec3 m_camera_pos;
    glm::vec3 m_camera_front;
    glm::vec3 m_camera_up;
};
