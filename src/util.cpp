#include "util.hpp"

#include <glm/ext/vector_double2.hpp>

glm::dvec2 worldToScreen(glm::dvec2 position)
{
    glm::dvec2 screen_position{};

    screen_position.x = (position.x * SCALING_FACTOR) + WIDTH / 2.0;
    screen_position.y = (HEIGHT - position.y * SCALING_FACTOR) - HEIGHT / 2.0;

    return screen_position;
}
