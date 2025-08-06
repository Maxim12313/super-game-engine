#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <iterator>
#include <memory>
#include <stack>
class Window;
class Color;
class WorldShader;
class Camera2D;

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

class Drawer {
public:
    Drawer();

    void begin_camera(std::shared_ptr<Camera2D> camera);
    void end_camera();
    void set_background_color(Color color) const;
    void clear() const;
    void queue_rectangle(double x, double y, double w, double h) const;
    void execute_draw() const;

private:
    uint32_t m_clear_bits;
    uint32_t m_square_vao;
    std::unique_ptr<WorldShader> m_shader;
    std::shared_ptr<Camera2D> m_camera;
    std::stack<Rect> m_rects;
};
