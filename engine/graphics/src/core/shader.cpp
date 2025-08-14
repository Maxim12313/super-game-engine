#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "constants.hpp"
#include "utils/macros.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <print>
#include <sstream>

namespace graphics {
// helpers ********
std::string read_file(const std::string &path) {
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
        return "";
    }
}

void compile_shader(const std::string &name, const std::string &shader_code,
                    uint32_t shader_id) {

    const char *code = shader_code.c_str();
    glShaderSource(shader_id, 1, &code, nullptr);
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

// shader class public ********
Shader::Shader(const std::string &vertex_path,
               const std::string &fragment_path) {
    m_id = glCreateProgram();

    // build shaders
    std::string vertex_code = read_file(vertex_path);
    LOG_DEBUG("vertex_code:\n{}", vertex_code.c_str());
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader("vertex", vertex_code, vertex_shader);
    glAttachShader(m_id, vertex_shader);

    std::string fragment_code = read_file(fragment_path);
    LOG_DEBUG("fragment_code:\n{}", fragment_code.c_str());
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader("fragment", fragment_code, fragment_shader);
    glAttachShader(m_id, fragment_shader);

    // build program
    compile_program(m_id);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // TODO: decide if necessary
    use();
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::set_int(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::set_float(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::set_bool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), int(value));
}
void Shader::set_mat4(const std::string &name, const float *value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                       value);
}

void Shader::set_vec4(const std::string &name, float a, float b, float c,
                      float d) const {
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), a, b, c, d);
}

void Shader::set_vec3(const std::string &name, float a, float b,
                      float c) const {
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), a, b, c);
}
} // namespace graphics
