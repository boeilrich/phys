#pragma once

constexpr double SCALING_FACTOR = 10.0;
constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

using Vec2 = struct Vec2 {
    double x{};
    double y{};
};

Vec2 worldToScreen(Vec2 position);
