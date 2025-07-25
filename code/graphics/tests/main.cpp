#include "graphics/camera.hpp"
#include "graphics/clock.hpp"
#include "graphics/glad_utils.hpp"
#include "graphics/window.hpp"
#include "utils/macros.hpp"
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <graphics/shader.hpp>
#include <graphics/context.hpp>
#include <graphics/constants.hpp>
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

const float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

const glm::vec3 cube_positions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

void runner() {
    // g_window.add_mouse_callback(mouse_callback);

    Window window(window::WIDTH, window::HEIGHT, "next");
    Camera camera;
    Shader shader(paths::SHADER_DIR / "texture_vertex.glsl",
                  paths::SHADER_DIR / "texture_fragment.glsl");

    Clock game_clock(window::FPS);

    uint32_t vao = gen_vertex_array();
    glBindVertexArray(vao);
    configure_draw_data(vertices, sizeof(vertices));
    uint32_t texture0 =
        configure_texture(paths::IMAGE_DIR / "container.jpg", GL_RGB);
    uint32_t texture1 =
        configure_texture(paths::IMAGE_DIR / "awesomeface.png", GL_RGBA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    shader.use();
    shader.set_int("texture0", 0);
    shader.set_int("texture1", 1);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    uint32_t clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    glm::mat4 projection(1.0f);
    projection =
        glm::perspective(glm::radians(45.0), window::RATIO, 0.1, 1000.0);
    shader.set_mat4("projection", glm::value_ptr(projection));

    while (!window.should_close()) {
        double dt = game_clock.update_dt();
        double avg_fps = game_clock.avg_fps();
        // LOG_DEBUG("avg fps: {}", avg_fps);

        handle_input(window, dt);
        camera.handle_input(window, dt);

        glClear(clear_bits);

        shader.use();

        auto view = camera.view();
        shader.set_mat4("view", glm::value_ptr(view));

        glBindVertexArray(vao);
        size_t size = sizeof(cube_positions) / sizeof(glm::vec3);
        for (size_t i = 0; i < size; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cube_positions[i]);
            float angle = 20 * i + 100 * glfwGetTime();
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3{1.0, 0.3, 0.5});
            shader.set_mat4("model", glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        window.end_drawing();
        game_clock.adjust_fps();
    }
}
