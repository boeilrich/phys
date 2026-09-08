#include "simulation.hpp"

#include <cmath>
#include <numbers>
#include <optional>
#include <random>
#include <vector>

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_double3.hpp>
#include <glm/ext/vector_double4.hpp>
#include <glm/geometric.hpp>
#include <raylib.h>

#include "aabb.hpp"
#include "body.hpp"

constexpr double DAMPENING_FACTOR = 0.8;
constexpr double RESTITUTION = 0.8;

void Simulation::tick()
{
    for (auto& body : bodies_) {
        body.tick(TIMESTEP);
    }

    for (auto& body : bodies_) {
        body.applyAcceleration(glm::dvec2(0.0, -9.81));
    }

    for (unsigned int i = 0; i < 8; i++) {
        for (auto& body : bodies_) {
            processBoundaryConstraint(body);
        }
        processBodyCollisions();
    }
}

void Simulation::processBoundaryConstraint(Body& body)
{
    glm::dvec2 position = body.getPosition();
    glm::dvec2 velocity = body.getVelocity();

    glm::dvec4 error = area_.findBodyCrossingError(body);

    if (error.x > 0) {
        velocity.x = -velocity.x * DAMPENING_FACTOR;
        position.x = position.x + error.x;
    }

    if (error.y > 0) {
        velocity.x = -velocity.x * DAMPENING_FACTOR;
        position.x = position.x - error.y;
    }

    if (error.z > 0) {
        velocity.y = -velocity.y * DAMPENING_FACTOR;
        position.y = position.y + error.z;
    }

    if (error.w > 0) {
        velocity.y = -velocity.y * DAMPENING_FACTOR;
        position.y = position.y - error.w;
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

            Body& body1 = *body1_it;
            Body& body2 = *body2_it;

            glm::dvec2 delta_position = body1.getPosition() - body2.getPosition();
            double distance = glm::length(delta_position);

            if (distance == 0 || body1.getRadius() + body2.getRadius() < distance) {
                continue;
            }

            glm::dvec2 normal = glm::normalize(delta_position);
            double collision_depth = body1.getRadius() + (body2.getRadius() - distance);

            glm::dvec2 relative_velocity = body1.getVelocity() - body2.getVelocity();
            double velocity_along_normal = glm::dot(relative_velocity, normal);

            if (velocity_along_normal >= 0.0) {
                continue;
            }

            double inverse_mass1 = 1.0 / body1.getMass();
            double inverse_mass2 = 1.0 / body2.getMass();

            double impulse_magnitude = -(1.0 + RESTITUTION) * velocity_along_normal / (inverse_mass1 + inverse_mass2);

            glm::dvec2 impulse = impulse_magnitude * normal;

            body1.setVelocity(body1.getVelocity() + inverse_mass1 * impulse);
            body2.setVelocity(body2.getVelocity() - inverse_mass2 * impulse);

            body1.setPosition(body1.getPosition() + normal * collision_depth / 2.0);
            body2.setPosition(body2.getPosition() - normal * collision_depth / 2.0);
        }
    }
}

void Simulation::addBody(Body body)
{
    bodies_.push_back(body);
}

void Simulation::addRandomBodies(unsigned int count)
{
    std::random_device r;

    std::default_random_engine e1(r());

    std::uniform_real_distribution<double> radius_distribution(0.1, 2);
    std::uniform_real_distribution<double> acceleration_distribution(100, 500);
    std::uniform_real_distribution<double> color_distribution(0.0, 1.0);

    std::uniform_real_distribution<double> x_distribution(area_.getPosition().x - area_.getWidth(),
                                                          area_.getPosition().x + area_.getWidth());

    std::uniform_real_distribution<double> y_distribution(area_.getPosition().y - area_.getHeight(),
                                                          area_.getPosition().y + area_.getHeight());

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

const std::vector<Body>& Simulation::getBodies() const noexcept
{
    return bodies_;
}
