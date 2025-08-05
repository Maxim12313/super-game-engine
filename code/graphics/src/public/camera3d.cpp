#include "graphics/camera3d.hpp"
#include "graphics/window.hpp"
#include "../core/constants.hpp"
#include "utils/macros.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

// constants *********
constexpr double PITCH_LOW = -89;
constexpr double PITCH_HIGH = 89;
constexpr double FOV_LOW = 1;
constexpr double FOV_HIGH = 90;

// helpers *********

// [low, high]
double bound_val(double val, double low, double high) {
    if (val < low)
        return low;
    if (val > high)
        return high;
    return val;
}

glm::vec3 calculate_camera_front(double yaw, double pitch) {
    glm::vec3 dir;
    double rad_yaw = glm::radians(yaw);
    double rad_pitch = glm::radians(pitch);
    dir.x = cos(rad_yaw) * cos(rad_pitch);

    dir.y = sin(rad_pitch);
    dir.z = sin(rad_yaw) * cos(rad_pitch);
    return glm::normalize(dir);
}

glm::vec3 calculate_camera_right(glm::vec3 camera_front, glm::vec3 camera_up) {
    return glm::normalize(glm::cross(camera_front, camera_up));
}

// class public *********
Camera3D::Camera3D(double fov, double z_near, double z_far)
    : Camera2D(), m_yaw(-90), m_pitch(0), m_first_mouse(true), m_fov(fov),
      m_z_near(z_near), m_z_far(z_far) {
}

void Camera3D::change_fov(double amount) {
    m_fov = bound_val(m_fov + amount, FOV_LOW, FOV_HIGH);
}

void Camera3D::move_cursor(double x, double y, double amount) {
    if (m_first_mouse) {
        m_prev_x = x;
        m_prev_y = y;
        m_first_mouse = false;
        return;
    }
    double dx = (x - m_prev_x) * amount;
    double dy = (y - m_prev_y) * amount;

    m_yaw += dx;
    m_pitch = bound_val(m_pitch - dy, PITCH_LOW, PITCH_HIGH);

    m_camera_front = calculate_camera_front(m_yaw, m_pitch);
    m_camera_right = calculate_camera_right(m_camera_front, m_camera_up);

    m_prev_x = x;
    m_prev_y = y;
}

glm::mat4 Camera3D::projection(double width, double height) const {
    double aspect_ratio = width / height;
    return glm::perspective(glm::radians(m_fov), aspect_ratio, m_z_near,
                            m_z_far);
}
