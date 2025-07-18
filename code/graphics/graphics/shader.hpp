#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

class Shader {

public:
    Shader(std::string vertex_path, std::string fragment_path);
    void use() const;
    void set_int(const char *name, int value) const;
    void set_float(const char *name, float value) const;
    void set_bool(const char *name, bool value) const;

private:
    uint32_t m_id;
};
