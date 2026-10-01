#include "simulation.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numbers>
#include <random>
#include <vector>

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_double3.hpp>
#include <glm/ext/vector_double4.hpp>
#include <glm/geometric.hpp>
#include <raylib.h>

#include "aabb.hpp"
#include "circle.hpp"

constexpr double DAMPENING_FACTOR = 0.9;
constexpr double RESTITUTION = 0.9;

void Simulation::tick()
{
    for (auto& body : bodies_) {
        body.tick(TIMESTEP);
    }

    for (auto& body : bodies_) {
        body.applyAcceleration(glm::dvec2(0.0, -9.81));
    }

    for (unsigned int i = 0; i < 8; i++) {
        processBodyCollisions();
        for (auto& body : bodies_) {
            processBoundaryConstraint(body);
        }
    }
}

void Simulation::processBoundaryConstraint(Circle& body)
{
    glm::dvec2 position = body.getPosition();
    glm::dvec2 velocity = body.getVelocity();

    CrossingError error = area_.findBodyCrossingError(body);

    if (error.top > 0 && velocity.y > 0.0) {
        velocity.y = -velocity.y * DAMPENING_FACTOR;
    }

    if (error.bottom > 0 && velocity.y < 0.0) {
        velocity.y = -velocity.y * DAMPENING_FACTOR;
    }

    if (error.left > 0 && velocity.x < 0.0) {
        velocity.x = -velocity.x * DAMPENING_FACTOR;
    }

    if (error.right > 0 && velocity.x > 0.0) {
        velocity.x = -velocity.x * DAMPENING_FACTOR;
    }

    position.y = position.y - std::max(error.top, 0.0);
    position.y = position.y + std::max(error.bottom, 0.0);
    position.x = position.x + std::max(error.left, 0.0);
    position.x = position.x - std::max(error.right, 0.0);

    body.setVelocity(velocity);
    body.setPosition(position);
}

void Simulation::processBodyCollisions()
{
    for (auto body1_it = bodies_.begin(); body1_it != bodies_.end(); ++body1_it) {
        for (auto body2_it = std::next(body1_it); body2_it != bodies_.end(); ++body2_it) {
            Circle& body1 = *body1_it;
            Circle& body2 = *body2_it;

            // Positional correction of the two bodies
            glm::dvec2 delta_position = body1.getPosition() - body2.getPosition();
            double distance = glm::length(delta_position);
            double minimum_distance = body1.getRadius() + body2.getRadius();

            if (distance >= minimum_distance) {
                continue;
            }

            glm::dvec2 normal = (distance > 0.0) ? glm::normalize(delta_position) : glm::dvec2(1.0, 0.0);
            double collision_depth = body1.getRadius() + (body2.getRadius() - distance);

            double inverse_mass1 = 1.0 / body1.getMass();
            double inverse_mass2 = 1.0 / body2.getMass();

            double total_inverse_mass = inverse_mass1 + inverse_mass2;

            body1.setPosition(body1.getPosition() + normal * collision_depth * (inverse_mass1 / total_inverse_mass));
            body2.setPosition(body2.getPosition() - normal * collision_depth * (inverse_mass2 / total_inverse_mass));

            // Velocity correction
            glm::dvec2 relative_velocity = body1.getVelocity() - body2.getVelocity();
            double velocity_along_normal = glm::dot(relative_velocity, normal);

            if (velocity_along_normal >= 0.0) {
                continue;
            }

            double impulse_magnitude = 0;
            if (-velocity_along_normal >= -0.5) {
                impulse_magnitude = -(1.0 + 0) * velocity_along_normal / (inverse_mass1 + inverse_mass2);
            } else {
                impulse_magnitude = -(1.0 + RESTITUTION) * velocity_along_normal / (inverse_mass1 + inverse_mass2);
            }

            glm::dvec2 impulse = impulse_magnitude * normal;

            body1.setVelocity(body1.getVelocity() + inverse_mass1 * impulse);
            body2.setVelocity(body2.getVelocity() - inverse_mass2 * impulse);
        }
    }
}

void Simulation::addBody(Circle body)
{
    bodies_.push_back(body);
}

void Simulation::addRandomBodies(unsigned int count)
{
    std::random_device r;

    std::default_random_engine e1(r());

    std::uniform_real_distribution<double> radius_distribution(0.1, 2);
    std::uniform_real_distribution<double> acceleration_distribution(-500, 500);
    std::uniform_real_distribution<double> color_distribution(0.0, 1.0);

    std::uniform_real_distribution<double> x_distribution(area_.getPosition().x - area_.getWidth() / 2,
                                                          area_.getPosition().x + area_.getWidth() / 2);

    std::uniform_real_distribution<double> y_distribution(area_.getPosition().y - area_.getHeight() / 2,
                                                          area_.getPosition().y + area_.getHeight() / 2);

    for (unsigned int i = 0; i < count; i++) {
        double x = x_distribution(e1);
        double y = y_distribution(e1);
        double radius = radius_distribution(e1);

        bodies_.emplace_back(glm::dvec2(x, y), std::pow(radius, 2) * std::numbers::pi, radius,
                             glm::dvec3(color_distribution(e1), color_distribution(e1), color_distribution(e1)));
        bodies_.back().applyAcceleration(glm::dvec2(acceleration_distribution(e1), acceleration_distribution(e1)));
    }
}

const AABoundingBox& Simulation::getBoundingBox()
{
    return area_;
}

const std::vector<Circle>& Simulation::getBodies() const noexcept
{
    return bodies_;
}
