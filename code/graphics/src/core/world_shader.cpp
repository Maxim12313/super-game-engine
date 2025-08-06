#include "world_shader.hpp"
#include "constants.hpp"
#include <glm/gtc/type_ptr.hpp>

WorldShader::WorldShader(const std::string &vertex_path,
                         const std::string &fragment_path)
    : Shader(vertex_path, fragment_path) {

    use();
    const float *identity = glm::value_ptr(math::IDENTITY);
    set_model(identity);
    set_view(identity);
    set_projection(identity);
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
