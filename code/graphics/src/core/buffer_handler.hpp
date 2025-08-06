#pragma once
#include <cstddef>
#include <cstdint>
#include <filesystem>
uint32_t configure_vao(const float vertices[], size_t count);
void configure_indices(const uint32_t indices[], size_t n);
uint32_t configure_texture(std::filesystem::path file_path, uint32_t format);
