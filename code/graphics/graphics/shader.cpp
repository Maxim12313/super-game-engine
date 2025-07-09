#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "utils/macros.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <print>
#include <sstream>

using std::cout;

std::string read_file(const char *path) {
    std::ifstream file;
    std::stringstream stream;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
        return stream.str();
    } catch (std::ifstream::failure e) {
        LOG_ERROR("could not read path: {}", path);
        ASSERT(false);
    }
}

void compile_shader(const char *name, const char *shader_code,
                    uint32_t shader_id) {

    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);

    int success;
    char log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, nullptr, log);
        LOG_ERROR("Shader {} compilation failed: {}", name, log);
    }
}

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    id = glCreateProgram();

    // prepare shaders
    std::string vertex_code = read_file(vertex_path);
    LOG_DEBUG("vertex_code:\n {}", vertex_code.c_str());
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader("vertex", vertex_code.c_str(), vertex_shader);
    glAttachShader(id, vertex_shader);
    glDeleteShader(vertex_shader);

    std::string fragment_code = read_file(fragment_path);
    LOG_DEBUG("fragment_code:\n {}", fragment_code.c_str());
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader("fragment", fragment_code.c_str(), fragment_shader);
    glAttachShader(id, fragment_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() const {
    glUseProgram(id);
}
