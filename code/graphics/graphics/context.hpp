#pragma once
#include <cstddef>
#include <cstdint>
#include <filesystem>
void configure_draw_data(const float vertices[], size_t n);
void configure_draw_indices(const uint32_t indices[], size_t n);
uint32_t configure_texture(std::filesystem::path file_path, uint32_t format);
