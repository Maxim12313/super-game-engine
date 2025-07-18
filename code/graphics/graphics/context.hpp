#pragma once
#include <cstddef>
#include <cstdint>
#include <filesystem>
class GLFWwindow;

void init_context();
void destroy_context();
GLFWwindow *create_window(int w, int h, const char *name);

void configure_draw_data(float vertices[], size_t n);
void configure_draw_indices(uint32_t indices[], size_t n);
uint32_t configure_texture(std::filesystem::path file_path, uint32_t format);
