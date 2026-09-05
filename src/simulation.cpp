#include "simulation.hpp"

#include <optional>
#include <vector>

#include <glm/ext/vector_double2.hpp>
#include <raylib.h>

#include "aabb.hpp"
#include "body.hpp"

constexpr double DAMPENING_FACTOR = 0.6;

void Simulation::tick()
{
    for (auto& body : bodies_) {
        body.applyAcceleration(glm::dvec2(0.0, -9.81));
    }

    for (auto& body : bodies_) {
        body.tick();

        double radius = body.getRadius();
        glm::dvec2 position = body.getPosition();
        glm::dvec2 velocity = body.getVelocity();
        glm::dvec2 area_position = area_.getPosition();

        std::optional<Side> side = area_.findBodyCrossingSide(body);
        if (!side)
            continue;

        switch (*side) {
            case Side::Top:
                velocity.y = -velocity.y * DAMPENING_FACTOR;
                position.y = (area_position.y + area_.getHeight() / 2.0) - radius;
                break;
            case Side::Bottom:
                velocity.y = -velocity.y * DAMPENING_FACTOR;
                position.y = (area_position.y - area_.getHeight() / 2.0) + radius;
                break;
            case Side::Left:
                velocity.x = -velocity.x * DAMPENING_FACTOR;
                position.x = (area_position.x - area_.getWidth() / 2.0) + radius;
                break;
            case Side::Right:
                velocity.x = -velocity.x * DAMPENING_FACTOR;
                position.x = (area_position.x + area_.getWidth() / 2.0) - radius;
                break;
        }

        body.setVelocity(velocity);
        body.setPosition(position);
    }
}

void Simulation::addBody(Body body)
{
    bodies_.push_back(body);
}

const AABoundingBox& Simulation::getBoundingBox()
{
    return area_;
}

const std::vector<Body>& Simulation::getBodies() const noexcept
{
    return bodies_;
}
