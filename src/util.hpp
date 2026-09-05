#pragma once

#include <glm/ext/vector_double2.hpp>

constexpr double SCALING_FACTOR = 10.0;
constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

glm::dvec2 worldToScreen(glm::dvec2 position);
