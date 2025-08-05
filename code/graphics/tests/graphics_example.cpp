#include "graphics/camera3d.hpp"
#include "../src/core/clock.hpp"
#include "graphics/window.hpp"
#include "../src/core/shader.hpp"
#include "../src/core/buffer_handler.hpp"
#include "../src/core/constants.hpp"
#include "utils/macros.hpp"

#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>

void runner();

int main() {
    try {
        runner();
        return 0;
    } catch (std::exception &e) {
        LOG_ERROR("{}", e.what());
        return 1;
    }
}

void handle_input(Window &window, Camera3D &camera, double dt) {
    if (window.key_status(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window.set_should_close();
    }

    const float camera_speed = 10 * dt;
    if (window.is_key_pressed(GLFW_KEY_W))
        camera.move_direction(Direction::FORWARD, camera_speed);
    if (window.is_key_pressed(GLFW_KEY_S))
        camera.move_direction(Direction::BACKWARD, camera_speed);
    if (window.is_key_pressed(GLFW_KEY_D))
        camera.move_direction(Direction::RIGHT, camera_speed);
    if (window.is_key_pressed(GLFW_KEY_A))
        camera.move_direction(Direction::LEFT, camera_speed);
    if (window.is_key_pressed(GLFW_KEY_SPACE))
        camera.move_direction(Direction::UP, camera_speed);
    if (window.is_key_pressed(GLFW_KEY_LEFT_SHIFT))
        camera.move_direction(Direction::DOWN, camera_speed);

    const float sensitivity = 5 * dt;
    glm::vec2 pos = window.cursor_pos();
    camera.move_cursor(pos.x, pos.y, sensitivity);

    double fov_dt = 45 * dt;
    if (window.is_key_pressed(GLFW_KEY_O)) {
        camera.change_fov(fov_dt);
    }
    if (window.is_key_pressed(GLFW_KEY_P)) {
        camera.change_fov(-fov_dt);
    }
}

void runner() {
    Window window;
    Camera3D camera;
}
