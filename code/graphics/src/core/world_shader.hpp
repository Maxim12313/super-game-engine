#pragma once
#include "shader.hpp"

class WorldShader : public Shader {
public:
    WorldShader(const std::string &vertex_path,
                const std::string &fragment_path);

    void set_model(const float *value) const;
    void set_view(const float *value) const;
    void set_projection(const float *value) const;
};
