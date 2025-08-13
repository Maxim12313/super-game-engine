#include "graphics/camera2d.hpp"
#include "graphics/window.hpp"
#include "../core/constants.hpp"
#include "utils/macros.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace graphics {

// class public *********
Camera2D::Camera2D(double x, double y, double z, double z_near, double z_far)
    : m_camera_pos(x, y, z), m_camera_front(0, 0, -1), m_camera_up(0, 1, 0),
      m_camera_right(glm::normalize(glm::cross(m_camera_front, m_camera_up))),
      m_z_near(z_near), m_z_far(z_far) {
}

void Camera2D::move_direction(Direction dir, double amount) {
    switch (dir) {
        case Direction::Up:
            move_y(amount);
            break;
        case Direction::Right:
            move_x(amount);
            break;
        case Direction::Forward:
            move_z(amount);
            break;
        case Direction::Down:
            move_y(-amount);
            break;
        case Direction::Left:
            move_x(-amount);
            break;
        case Direction::Backward:
            move_z(-amount);
            break;
    }
}

void Camera2D::move(glm::vec3 velocity) {
    m_camera_pos += velocity;
}

const glm::vec3 &Camera2D::pos() const {
    return m_camera_pos;
}

glm::mat4 Camera2D::view() const {
    return glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front,
                       m_camera_up);
}

glm::mat4 Camera2D::projection(double width, double height) const {
    return glm::ortho(0.0, width, 0.0, height, m_z_near, m_z_far);
}

// class private *********
void Camera2D::move_z(float amount) {
    m_camera_pos += amount * m_camera_front;
}

void Camera2D::move_x(float amount) {
    m_camera_pos += amount * m_camera_right;
}

void Camera2D::move_y(float amount) {
    m_camera_pos += amount * m_camera_up;
}
} // namespace graphics
