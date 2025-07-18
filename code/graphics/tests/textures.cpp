#include "graphics/glad_utils.hpp"
#include "utils/macros.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <graphics/shader.hpp>
#include <graphics/context.hpp>
#include <graphics/config.hpp>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>

void processInput(GLFWwindow *window);

int main() {
    init_context();
    GLFWwindow *window = create_window(800, 600, "reading test");
    if (window == nullptr) {
        LOG_ERROR("failed to initialize window");
        destroy_context();
        return 1;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("failed to initialize glad");
        return 1;
    }

    stbi_set_flip_vertically_on_load(true);

    Shader shader(paths::SHADER_DIR / "texture_vertex.glsl",
                  paths::SHADER_DIR / "texture_fragment.glsl");

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    uint32_t indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    uint32_t vao = gen_vertex_array();
    glBindVertexArray(vao);
    configure_draw_data(vertices, sizeof(vertices));
    configure_draw_indices(indices, sizeof(indices));
    uint32_t texture0 =
        configure_texture(paths::IMAGE_DIR / "container.jpg", GL_RGB);
    uint32_t texture1 =
        configure_texture(paths::IMAGE_DIR / "awesomeface.png", GL_RGBA);

    shader.use();
    shader.set_int("texture0", 0);
    shader.set_int("texture1", 1);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    shader.set_mat4("transform", glm::value_ptr(trans));

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy_context();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
