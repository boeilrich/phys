#include "simulation.hpp"

#include <optional>
#include <vector>

#include <glm/ext/vector_double2.hpp>
#include <glm/geometric.hpp>
#include <raylib.h>

#include "aabb.hpp"
#include "body.hpp"

constexpr double DAMPENING_FACTOR = 0.8;
constexpr double RESTITUTION = 0.8;

void Simulation::tick()
{
    for (auto& body : bodies_) {
        body.applyAcceleration(glm::dvec2(0.0, -9.81));
    }

    for (auto& body : bodies_) {
        body.tick(TIMESTEP);
        processBoundaryConstraint(body);
    }

    processBodyCollisions();
}

void Simulation::processBoundaryConstraint(Body& body)
{
    glm::dvec2 area_position = area_.getPosition();
    double area_height = area_.getHeight();
    double area_width = area_.getWidth();

    double radius = body.getRadius();
    glm::dvec2 position = body.getPosition();
    glm::dvec2 velocity = body.getVelocity();

    std::optional<Side> side = area_.findBodyCrossingSide(body);
    if (!side)
        return;

    switch (*side) {
        case Side::Top:
            velocity.y = -velocity.y * DAMPENING_FACTOR;
            position.y = (area_position.y + area_height / 2.0) - radius;
            break;
        case Side::Bottom:
            velocity.y = -velocity.y * DAMPENING_FACTOR;
            position.y = (area_position.y - area_height / 2.0) + radius;
            break;
        case Side::Left:
            velocity.x = -velocity.x * DAMPENING_FACTOR;
            position.x = (area_position.x - area_width / 2.0) + radius;
            break;
        case Side::Right:
            velocity.x = -velocity.x * DAMPENING_FACTOR;
            position.x = (area_position.x + area_width / 2.0) - radius;
            break;
    }

    body.setVelocity(velocity);
    body.setPosition(position);
}

void Simulation::processBodyCollisions()
{
    for (auto body1_it = bodies_.begin(); body1_it != bodies_.end(); ++body1_it) {
        for (auto body2_it = std::next(body1_it); body2_it != bodies_.end(); ++body2_it) {
            if (body1_it == body2_it) {
                continue;
            }

            glm::dvec2 delta = (*body1_it).getPosition() - (*body2_it).getPosition();

            double distance = glm::length(delta);

            if (distance > (*body1_it).getRadius() + (*body2_it).getRadius() || distance == 0) {
                continue;
            }

            double depth = ((*body1_it).getRadius() + (*body2_it).getRadius() - distance);

            glm::dvec2 collision_normal = glm::normalize(delta);

            glm::dvec2 relativeVelocity = (*body1_it).getVelocity() - (*body2_it).getVelocity();
            double velocityAlongNormal = glm::dot(relativeVelocity, collision_normal);

            if (velocityAlongNormal >= 0.0)
                continue;

            double inverseMass1 = 1.0 / (*body1_it).getMass();
            double inverseMass2 = 1.0 / (*body2_it).getMass();

            double impulseMagnitude = -(1.0 + RESTITUTION) * velocityAlongNormal / (inverseMass1 + inverseMass2);

            glm::dvec2 impulse = impulseMagnitude * collision_normal;

            (*body1_it).setVelocity((*body1_it).getVelocity() + inverseMass1 * impulse);
            (*body2_it).setVelocity((*body2_it).getVelocity() - inverseMass2 * impulse);

            (*body1_it).setPosition((*body1_it).getPosition() + collision_normal * depth / 2.0);
            (*body2_it).setPosition((*body2_it).getPosition() - collision_normal * depth / 2.0);
        }
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
