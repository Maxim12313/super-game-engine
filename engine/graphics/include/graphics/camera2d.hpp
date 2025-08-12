#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace graphics {

class Window;

enum class Direction { Up, Right, Forward, Down, Left, Backward };

class Camera2D {
public:
    Camera2D(double x = 0, double y = 0, double z = 0, double z_near = 0,
             double z_far = 1);
    void move_direction(Direction dir, double amount);
    glm::mat4 view() const;
    const glm::vec3 &pos() const;
    virtual glm::mat4 projection(double width, double height) const;

private:
    void move_z(float amount);
    void move_x(float amount);
    void move_y(float amount);

protected:
    glm::vec3 m_camera_pos;
    glm::vec3 m_camera_front;
    glm::vec3 m_camera_up;
    glm::vec3 m_camera_right;
    double m_z_near;
    double m_z_far;
};

}; // namespace graphics
