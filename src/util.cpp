#include "util.hpp"

Vec2 worldToScreen(Vec2 position)
{
    Vec2 screen_position{};

    screen_position.x = position.x * SCALING_FACTOR;
    screen_position.y = HEIGHT - position.y * SCALING_FACTOR;

    return screen_position;
}
