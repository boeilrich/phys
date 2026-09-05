#include "util.hpp"

#include <glm/ext/vector_double2.hpp>
glm::dvec2 worldToScreen(glm::dvec2 position)
{
    return {position.x * PIXELS_PER_METER + WIDTH / 2.0, HEIGHT / 2.0 - position.y * PIXELS_PER_METER};
}
// glm::dvec2 worldToScreen(glm::dvec2 position)
// {
//     glm::dvec2 screen_position{};
//
//     screen_position.x = (position.x * PIXELS_PER_METER) + WIDTH / 2.0;
//     screen_position.y = (HEIGHT - position.y * PIXELS_PER_METER) - HEIGHT / 2.0;
//
//     return screen_position;
// }
