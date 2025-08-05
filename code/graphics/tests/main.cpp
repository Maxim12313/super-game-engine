#include "graphics/camera.hpp"
#include "../src/core/clock.hpp"
#include "../src/core/glad_utils.hpp"
#include "graphics/window.hpp"
#include "../src/core/shader.hpp"
#include "../src/core/context.hpp"
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

void handle_input(Window &window, Camera &camera, double dt) {
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
    double x, y;
    window.cursor_pos(x, y);
    camera.move_cursor(x, y, sensitivity);

    double fov_dt = 45 * dt;
    if (window.is_key_pressed(GLFW_KEY_O)) {
        camera.change_fov(fov_dt);
    }
    if (window.is_key_pressed(GLFW_KEY_P)) {
        camera.change_fov(-fov_dt);
    }
}

void runner() {
    // g_window.add_mouse_callback(mouse_callback);

    Window window;
    Camera camera;
    Shader shader(paths::SHADER_DIR / "texture_vertex.glsl",
                  paths::SHADER_DIR / "texture_fragment.glsl");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    uint32_t clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    while (!window.should_close()) {
        double dt = window.begin_update();
        handle_input(window, camera, dt);

        glClear(clear_bits);

        window.end_update();
    }
}
