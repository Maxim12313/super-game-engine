#pragma once

#include <cstdint>
#include <cstdio>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const std::string &vertex_path, const std::string &fragment_path);
    void use() const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_bool(const std::string &name, bool value) const;
    void set_mat4(const std::string &name, const float *value) const;
    void set_vec4(const std::string &name, float a, float b, float c,
                  float d) const;
    void set_vec3(const std::string &name, float a, float b, float c) const;

private:
    uint32_t m_id;
};
