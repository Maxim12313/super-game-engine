#include "../src/core/clock.hpp"
#include "graphics/color.hpp"
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

void handle_input(Window &window, double dt) {
    if (window.key_status(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window.set_should_close();
    }
}

void runner() {
    Window window;
    window.set_background(CYAN);
    while (!window.should_close()) {
        double dt = window.begin_update();
        window.end_update();
    }
}
