#pragma once
#include <glm/glm.hpp>
#include <filesystem>

namespace paths {
const auto RESOURCE_DIR = std::filesystem::path("code/graphics/resources");
const auto SHADER_DIR = RESOURCE_DIR / "shaders";
const auto IMAGE_DIR = RESOURCE_DIR / "images";
} // namespace paths

namespace window {
const int WIDTH = 1280;
const int HEIGHT = 800;
const double RATIO = double(WIDTH) / HEIGHT;
} // namespace window

namespace vectors {
const glm::vec3 UP(0, 1, 0);
const glm::vec3 LEFT(1, 0, 0);
const glm::vec3 RIGHT(0, 0, 1);
const glm::vec3 ZERO(0, 0, 0);
} // namespace vectors
