#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include "graphics/camera2d.hpp"
#include "graphics/drawer.hpp"
#include "graphics/event.hpp"
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

using namespace graphics;

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

void runner() {
    Window window;
    Camera2D camera;
    Drawer drawer(window.width(), window.height());
    drawer.set_background_color(CYAN);

    window.toggle_listen_key();

    drawer.begin_camera(camera);
    while (!window.should_close()) {
        double dt = window.begin_update();
        drawer.clear();

        while (true) {
            Event e = window.poll_event();
            if (e.type == EventType::None)
                break;

            switch (e.type) {
                case EventType::Key: {
                    KeyEvent data = e.data.key;
                    float speed = 500;
                    if (data.key == GLFW_KEY_A) {
                        camera.move_direction(Direction::Right, speed * dt);
                    }
                    if (data.key == GLFW_KEY_D) {
                        camera.move_direction(Direction::Left, speed * dt);
                    }
                    if (data.key == GLFW_KEY_W) {
                        camera.move_direction(Direction::Down, speed * dt);
                    }
                    if (data.key == GLFW_KEY_S) {
                        camera.move_direction(Direction::Up, speed * dt);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        drawer.queue_rectangle(0, 0, 100, 100, RED);
        drawer.execute_draw();

        window.end_update();
    }
    drawer.end_camera();
}
