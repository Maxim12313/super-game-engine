#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils/macros.hpp"
#include "world_shader.hpp"
#include "shapes.hpp"
#include "drawer.hpp"
#include "buffer_handler.hpp"
#include "graphics/color.hpp"
#include "../core/constants.hpp"

// class public ********
Drawer::Drawer() {
    m_shader = std::make_unique<WorldShader>(
        paths::SHADER_DIR / "color_vertex.glsl",
        paths::SHADER_DIR / "color_fragment.glsl");

    // this is for 3d
    glEnable(GL_DEPTH_TEST);

    m_clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    m_square_vao = configure_vao(internal::SQUARE_VERTICES.begin(),
                                 internal::SQUARE_VERTICES.size());
}

void Drawer::begin_camera(std::shared_ptr<Camera2D> camera) {
    ASSERT(!m_camera && "already existing camera context");
    m_camera = camera;
}
void Drawer::end_camera() {
    m_camera.reset();
}

void Drawer::set_background_color(Color color) const {
    glClearColor(color.red, color.green, color.blue, 1);
}

void Drawer::clear() const {
    glClear(m_clear_bits);
}

void Drawer::queue_rectangle(double x, double y, double w, double h) const {
    // TODO:
    ASSERT(false && "implement this");
}

void Drawer::execute_draw() const {
    // TODO:
    ASSERT(false && "implement this");

    // glm::mat4 model = glm::translate(math::IDENTITY, glm::vec3(x, y, 0));
    // m_shader->set_mat4("model", glm::value_ptr(model));

    glBindVertexArray(m_square_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
