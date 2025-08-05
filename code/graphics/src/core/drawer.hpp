#pragma once
#include <glm/ext/vector_float2.hpp>
#include <iterator>
class Window;
class Color;
class Shader;

class Drawer {
public:
    Drawer();

    void set_background_color(Color color) const;
    void clear() const;
    void draw_rectangle(int x, int y, int w, int h, int window_width,
                        int window_height) const;

private:
    uint32_t m_clear_bits;
    uint32_t m_square_vao;
};

// void clear_background(Window &window);
// void draw_rectangle(glm::vec2 position, glm::vec2 dimensions, Color color);
//
// // such as vector<glm::vec2> points
// template <typename Iterator>
// void draw_polygon(Iterator points_begin, Iterator points_end, Color color);
