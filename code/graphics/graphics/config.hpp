#pragma once
#include <filesystem>

namespace paths {
const auto RESOURCE_DIR = std::filesystem::path("code/graphics/resources");
const auto SHADER_DIR = RESOURCE_DIR / "shaders";
const auto IMAGE_DIR = RESOURCE_DIR / "images";

} // namespace paths
