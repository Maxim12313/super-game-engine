#include "world_shader.hpp"
#include "graphics/structs.hpp"
#include "constants.hpp"
#include "graphics/constants.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace graphics {

WorldShader::WorldShader(const std::string &vertex_path,
                         const std::string &fragment_path)
    : Shader(vertex_path, fragment_path) {
    const float *identity = glm::value_ptr(math::IDENTITY);
    set_model(identity);
    set_view(identity);
    set_projection(identity);
    set_color(RED);
}

void WorldShader::set_model(const float *value) const {
    set_mat4("model", value);
}
void WorldShader::set_view(const float *value) const {
    set_mat4("view", value);
}
void WorldShader::set_projection(const float *value) const {
    set_mat4("projection", value);
}

void WorldShader::set_color(Color color) const {
    set_vec4("color", color.red / COLOR_SCALE, color.blue / COLOR_SCALE,
             color.green / COLOR_SCALE, color.alpha / COLOR_SCALE);
}
} // namespace graphics
