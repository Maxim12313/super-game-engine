#pragma once
#include <glm/glm.hpp>
#include <filesystem>

namespace paths {
const auto RESOURCE_DIR = std::filesystem::path("code/graphics/resources");
const auto SHADER_DIR = RESOURCE_DIR / "shaders";
const auto IMAGE_DIR = RESOURCE_DIR / "images";
} // namespace paths

// initial constexprants
namespace window {
constexpr int WIDTH = 1280;
constexpr int HEIGHT = 800;
constexpr double RATIO = double(WIDTH) / HEIGHT;
constexpr int FPS = 60;
inline const char *TITLE = "game engine";
} // namespace window

namespace vectors {
constexpr glm::vec3 UP(0, 1, 0);
constexpr glm::vec3 LEFT(1, 0, 0);
constexpr glm::vec3 RIGHT(0, 0, 1);
constexpr glm::vec3 ZERO(0, 0, 0);
} // namespace vectors

namespace camera {
constexpr double FOV = 45;
constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 1000;
constexpr double PITCH_LOW = -89;
constexpr double PITCH_HIGH = 89;
constexpr double FOV_LOW = 1;
constexpr double FOV_HIGH = 90;
}; // namespace camera
