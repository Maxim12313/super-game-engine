#pragma once
#include <glm/ext/vector_float2.hpp>
#include <iterator>
class Window;
class Color;
class Shader;

void clear_background(Window &window);
void draw_rectangle(glm::vec2 position, glm::vec2 dimensions, Color color);

// such as vector<glm::vec2> points
template <typename Iterator>
void draw_polygon(Iterator points_begin, Iterator points_end, Color color);
