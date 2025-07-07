#pragma once

#include <cstdint>
class Shader {
private:
    uint32_t id;

public:
    Shader(const char *vertex_path, const char *fragment_path);
    void use() const;
};
