#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <iterator>
#include <memory>
#include <queue>
#include "graphics/color.hpp"

namespace graphics {

class Window;
class Color;
class Camera2D;
class WorldShader;

struct Rect {
    double x;
    double y;
    double w;
    double h;
    Color color;
};

class Drawer {
public:
    Drawer(const int &width, const int &height);
    ~Drawer();
    void begin_camera(const Camera2D &camera);
    void end_camera();
    void set_background_color(Color color) const;
    void clear() const;
    void queue_rectangle(double x, double y, double w, double h, Color color);
    void execute_draw();

private:
    void set_transform_uniforms() const;

private:
    const int &m_width;
    const int &m_height;

    uint32_t m_clear_bits;
    uint32_t m_square_vao;
    std::unique_ptr<WorldShader> m_shader;
    const Camera2D *m_camera;
    std::queue<Rect> m_rects;
};
} // namespace graphics
