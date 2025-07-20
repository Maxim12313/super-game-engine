#pragma once
#include <glm/ext/vector_float3.hpp>

class Camera {
public:
    Camera();

private:
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
};
