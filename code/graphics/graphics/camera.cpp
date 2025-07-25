#include "camera.hpp"
#include "graphics/window.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

// class public *********

Camera::Camera()
    : m_yaw(-90), m_pitch(0), m_first_mouse(true), m_camera_pos(0, 0, 3),
      m_camera_front(0, 0, -1), m_camera_up(0, 1, 0) {
}

void Camera::handle_input(Window &window, double dt) {
    const float camera_speed = 10 * dt;
    if (window.key_status(GLFW_KEY_W) == GLFW_PRESS) {
        m_camera_pos += camera_speed * m_camera_front;
    }
    if (window.key_status(GLFW_KEY_S) == GLFW_PRESS) {
        m_camera_pos -= camera_speed * m_camera_front;
    }
    glm::vec3 camera_right =
        glm::normalize(glm::cross(m_camera_front, m_camera_up));
    if (window.key_status(GLFW_KEY_D) == GLFW_PRESS) {
        m_camera_pos += camera_speed * camera_right;
    }
    if (window.key_status(GLFW_KEY_A) == GLFW_PRESS) {
        m_camera_pos -= camera_speed * camera_right;
    }

    double x, y;
    window.cursor_pos(x, y);
    if (m_first_mouse) {
        m_prev_x = x;
        m_prev_y = y;
        m_first_mouse = false;
        return;
    }

    double dx = x - m_prev_x;
    double dy = y - m_prev_y;

    double sens = 0.1;
    dx *= sens;
    dy *= sens;

    m_yaw += dx;
    m_pitch -= dy;

    if (m_pitch > 89)
        m_pitch = 89;
    else if (m_pitch < -89)
        m_pitch = -89;

    glm::vec3 dir;
    double rad_yaw = glm::radians(m_yaw);
    double rad_pitch = glm::radians(m_pitch);
    dir.x = cos(rad_yaw) * cos(rad_pitch);
    dir.y = sin(rad_pitch);
    dir.z = sin(rad_yaw) * cos(rad_pitch);
    m_camera_front = glm::normalize(dir);

    m_prev_x = x;
    m_prev_y = y;
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front,
                       m_camera_up);
}
