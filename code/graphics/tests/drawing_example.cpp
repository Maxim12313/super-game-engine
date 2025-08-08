#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include "graphics/camera2d.hpp"
#include "../src/core/drawer.hpp"
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

void handle_input(Window &window, double dt) {
    if (window.key_status(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window.set_should_close();
    }
}

void runner() {
    Window window;
    Camera2D camera;
    Drawer drawer(window.width(), window.height());
    drawer.set_background_color(CYAN);

    drawer.begin_camera(&camera);
    while (!window.should_close()) {
        double dt = window.begin_update();
        drawer.clear();

        drawer.queue_rectangle(100, 300, 50, 100, BLUE);
        drawer.queue_rectangle(100, 300, 50, 100, BLUE);
        drawer.queue_rectangle(10, 10, 100, 100, PURPLE);
        drawer.execute_draw();

        window.end_update();
    }
    drawer.end_camera();
}
