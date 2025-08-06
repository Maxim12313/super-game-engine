#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils/macros.hpp"
#include "shapes.hpp"
#include "drawer.hpp"
#include "buffer_handler.hpp"
#include "constants.hpp"
#include "graphics/camera2d.hpp"

// helpers ********
glm::mat4 calculate_model_rect(int x, int y, int w, int h) {
    glm::mat4 model = glm::translate(math::IDENTITY, glm::vec3{x, y, 0});
    return glm::scale(model, glm::vec3{w, h, 1});
}

// class public ********
Drawer::Drawer(const double &width, const double &height)
    : m_width(width), m_height(height) {
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

void Drawer::queue_rectangle(double x, double y, double w, double h,
                             Color color) {
    m_rects.push(Rect{x, y, w, h});
}

void Drawer::execute_draw() {
    m_shader->use();

    set_transform_uniforms();
    m_shader->set_color(PURPLE);

    int x = 1;
    int y = 1;
    int w = 1;
    int h = 1;
    glm::mat4 model = calculate_model_rect(x, y, w, h);
    m_shader->set_model(glm::value_ptr(model));

    glBindVertexArray(m_square_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    //
    // // draw rects
    // glBindVertexArray(m_square_vao);
    // while (!m_rects.empty()) {
    //     auto [x, y, w, h, color] = m_rects.top();
    //     m_rects.pop();
    //
    //     glm::mat4 model = calculate_model_rect(x, y, w, h);
    //     m_shader->set_model(glm::value_ptr(model));
    //     m_shader->set_color(color);
    //     glDrawArrays(GL_TRIANGLES, 0, 6);
    // }
    // glBindVertexArray(0);
}

// class private ********
void Drawer::set_transform_uniforms() const {
    glm::mat4 projection;
    glm::mat4 view;
    if (!m_camera) {
        // set default identity mat
        projection = math::IDENTITY;
        view = math::IDENTITY;
    } else {
        // set camera mats
        projection = m_camera->projection(m_width, m_height);
        view = m_camera->view();
    }
    m_shader->set_view(glm::value_ptr(view));
    m_shader->set_projection(glm::value_ptr(projection));
}
