#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/macros.hpp>
#include <utils/stb_image.h>
#include "buffer_handler.hpp"
#include <filesystem>

// helpers ********
uint32_t gen_buffer() {
    uint32_t buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

uint32_t gen_vertex_array() {
    uint32_t vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

uint32_t gen_texture() {
    uint32_t texture;
    glGenTextures(1, &texture);
    return texture;
}

// functions ********
uint32_t configure_vao(const float vertices[], size_t n) {
    uint32_t vao = gen_vertex_array();
    glBindVertexArray(vao);

    uint32_t vbo = gen_buffer();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, n, vertices, GL_STATIC_DRAW);

    uint32_t stride = 3 * sizeof(float);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);

    return vao;
}

void configure_indices(const uint32_t indices[], size_t n) {
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
