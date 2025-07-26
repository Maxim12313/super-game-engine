#include "camera.hpp"
#include "graphics/window.hpp"
#include "constants.hpp"
#include "utils/macros.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

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

Camera::Camera(double fov, double z_near, double z_far)
    : m_yaw(-90), m_pitch(0), m_first_mouse(true), m_fov(fov), m_z_near(z_near),
      m_z_far(z_far), m_camera_pos(0, 0, 3), m_camera_front(0, 0, -1),
      m_camera_up(0, 1, 0),
      m_camera_right(glm::normalize(glm::cross(m_camera_front, m_camera_up))) {
}

void Camera::move_left(float amount) {
    move_x(-amount);
}
void Camera::move_right(float amount) {
    move_x(amount);
}
void Camera::move_forward(float amount) {
    move_z(amount);
}
void Camera::move_backward(float amount) {
    move_z(-amount);
}

void Camera::change_fov(double amount) {
    m_fov = bound_val(m_fov + amount, camera::FOV_LOW, camera::FOV_HIGH);
}

void Camera::move_cursor(double x, double y, double amount) {
    if (m_first_mouse) {
        m_prev_x = x;
        m_prev_y = y;
        m_first_mouse = false;
        return;
    }
    double dx = (x - m_prev_x) * amount;
    double dy = (y - m_prev_y) * amount;

    m_yaw += dx;
    m_pitch = bound_val(m_pitch - dy, camera::PITCH_LOW, camera::PITCH_HIGH);

    m_camera_front = calculate_camera_front(m_yaw, m_pitch);
    m_camera_right = calculate_camera_right(m_camera_front, m_camera_up);

    m_prev_x = x;
    m_prev_y = y;
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front,
                       m_camera_up);
}
glm::mat4 Camera::projection(double aspect_ratio) const {
    return glm::perspective(glm::radians(m_fov), aspect_ratio, m_z_near,
                            m_z_far);
}

// class private *********
void Camera::move_z(float amount) {
    m_camera_pos += amount * m_camera_front;
}

void Camera::move_x(float amount) {
    m_camera_pos += amount * m_camera_right;
}
