#pragma once

using Vec2 = struct Vec2 {
    double x{};
    double y{};
};

Vec2 worldToScreen(Vec2 position);
