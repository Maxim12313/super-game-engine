#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shapes.hpp"

#include "drawer.hpp"
#include "buffer_handler.hpp"
#include "graphics/color.hpp"

// class public ********
Drawer::Drawer() {
    // this is for 3d
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    m_square_vao = configure_vao(internal::SQUARE_VERTICES.begin(),
                                 internal::SQUARE_VERTICES.size());
}

void Drawer::set_background_color(Color color) const {
    glClearColor(color.red, color.green, color.blue, 1);
}

void Drawer::clear() const {
    glClear(m_clear_bits);
}

void Drawer::draw_rectangle(int x, int y, int w, int h, int window_width,
                            int window_height) const {
}
