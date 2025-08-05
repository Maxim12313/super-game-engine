#pragma once

#include <cstdint>
#include <cstdio>
#include <glm/glm.hpp>
#include <string>

constexpr size_t SHADER_MODE_2D = 0;
constexpr size_t SHADER_MODE_3D = 1;

class Shader {
public:
    Shader(const std::string &vertex_path, const std::string &fragment_path);
    void use() const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_bool(const std::string &name, bool value) const;
    void set_mat4(const std::string &name, float *value) const;

private:
    uint32_t m_id;
};

class ShaderManager {
public:
    // by default, we add simple 2d and 3d shaders
    ShaderManager();
    void set_mode(size_t idx);
    void add_shader(const std::string &vertex_path,
                    const std::string &fragment_path);
    const Shader &shader() const {
        return m_shaders[m_shader_idx];
    }

private:
    // can extend this with enum idx and array as well
    int m_shader_idx;
    std::vector<Shader> m_shaders;
};
