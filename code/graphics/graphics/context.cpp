#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/macros.hpp>
#include <utils/stb_image.h>
#include "context.hpp"
#include "graphics/glad_utils.hpp"
#include <filesystem>
#include "graphics/shader.hpp"

void init_context() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void destroy_context() {
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

GLFWwindow *create_window(int w, int h, const char *name) {
    GLFWwindow *window = glfwCreateWindow(w, h, name, nullptr, nullptr);
    if (window == nullptr)
        return nullptr;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

void configure_draw_data(float vertices[], size_t n) {
    uint32_t vbo = gen_buffer();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, n, vertices, GL_STATIC_DRAW);

    uint32_t stride = 8 * sizeof(float);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void configure_draw_indices(uint32_t indices[], size_t n) {
    uint32_t ebo = gen_buffer();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, indices, GL_STATIC_DRAW);
}

void set_texture_settings() {
    // when covering outside
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // when scaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// returns the texture
uint32_t configure_texture(std::filesystem::path file_path, uint32_t format) {
    uint32_t texture = gen_texture();
    glBindTexture(GL_TEXTURE_2D, texture);
    set_texture_settings();

    int w, h, channels;
    unsigned char *data = stbi_load(file_path.c_str(), &w, &h, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOG_ERROR("Cannot load image");
    }
    stbi_image_free(data);
    return texture;
}
