#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glad_utils.hpp"

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
