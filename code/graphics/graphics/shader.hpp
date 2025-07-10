#pragma once

#include <cstdint>
#include <string>

class Shader {
private:
    uint32_t id;

public:
    Shader(std::string vertex_path, std::string fragment_path);
    void use() const;
};
