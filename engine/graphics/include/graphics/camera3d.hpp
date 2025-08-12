#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include "graphics/camera2d.hpp"

namespace graphics {
class Window;

class Camera3D : public Camera2D {
public:
    Camera3D(double x = 0, double y = 0, double z = 0, double fov = 45,
             double z_near = 0.1, double z_far = 1000);
    void move_cursor(double x, double y, double amount);
    void change_fov(double amount);
    glm::mat4 projection(double width, double height) const override;

private:
    bool m_first_mouse;
    double m_yaw;
    double m_pitch;
    double m_prev_x; // default
    double m_prev_y; // default
    double m_fov;
};
} // namespace graphics
