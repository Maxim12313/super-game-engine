#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "utils/macros.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <print>
#include <sstream>

std::string read_file(std::string path) {
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

void compile_program(uint32_t id) {
    int success;
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    char log[512];
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, log);
        LOG_ERROR("Shader program compilation failed: {}", log);
    }
}

Shader::Shader(std::string vertex_path, std::string fragment_path) {
    m_id = glCreateProgram();

    // build shaders
    std::string vertex_code = read_file(vertex_path);
    LOG_DEBUG("vertex_code:\n{}", vertex_code.c_str());
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader("vertex", vertex_code.c_str(), vertex_shader);
    glAttachShader(m_id, vertex_shader);

    std::string fragment_code = read_file(fragment_path);
    LOG_DEBUG("fragment_code:\n{}", fragment_code.c_str());
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader("fragment", fragment_code.c_str(), fragment_shader);
    glAttachShader(m_id, fragment_shader);

    // build program
    compile_program(m_id);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::set_int(const char *name, int value) const {
    glUniform1i(glGetUniformLocation(m_id, name), value);
}
void Shader::set_float(const char *name, float value) const {
    glUniform1f(glGetUniformLocation(m_id, name), value);
}
void Shader::set_bool(const char *name, bool value) const {
    glUniform1i(glGetUniformLocation(m_id, name), int(value));
}
