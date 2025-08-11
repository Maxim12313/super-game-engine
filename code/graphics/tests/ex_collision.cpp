#include "graphics/collisions.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include "graphics/camera2d.hpp"
#include "graphics/drawer.hpp"
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

struct Player {
    glm::vec3 position;
    glm::vec2 dimensions;
    Color color;
};

void runner() {
    Window window;
    Camera2D camera;
    Drawer drawer(window.width(), window.height());
    drawer.set_background_color(CYAN);

    Player player;
    player.dimensions.x = 100;
    player.dimensions.y = 100;

    std::vector<Rect> rectangles = {{100, 300, 50, 100, BLUE},
                                    {200, 300, 50, 200, GRAY},
                                    {1000, 500, 788, 90, PURPLE}};

    drawer.begin_camera(camera);
    while (!window.should_close()) {
        double dt = window.begin_update();
        drawer.clear();

        float speed = 1000 * dt;
        if (window.is_key_pressed(GLFW_KEY_A)) {
            camera.move_direction(Direction::Left, speed);
        }
        if (window.is_key_pressed(GLFW_KEY_D)) {
            camera.move_direction(Direction::Right, speed);
        }
        if (window.is_key_pressed(GLFW_KEY_W)) {
            camera.move_direction(Direction::Up, speed);
        }
        if (window.is_key_pressed(GLFW_KEY_S)) {
            camera.move_direction(Direction::Down, speed);
        }

        player.position =
            glm::vec3{window.width() / 2, window.height() / 2, 0} +
            camera.pos();

        player.color = GREEN;
        for (auto [x, y, w, h, color] : rectangles) {
            if (rect_colliding(player.position.x, player.position.y,
                               player.dimensions.x, player.dimensions.y, x, y,
                               w, h)) {
                player.color = RED;
                break;
            }
        }

        drawer.queue_rectangle(player.position.x, player.position.y,
                               player.dimensions.x, player.dimensions.y,
                               player.color);

        for (auto [x, y, w, h, color] : rectangles) {
            drawer.queue_rectangle(x, y, w, h, color);
        }

        drawer.execute_draw();

        window.end_update();
    }
    drawer.end_camera();
}
