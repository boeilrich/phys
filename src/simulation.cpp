#include "simulation.hpp"

#include <cmath>
#include <vector>

#include "body.hpp"
#include "main.hpp"

void Simulation::tick()
{
    for (auto body1 = bodies_.begin(); body1 != bodies_.end(); ++body1) {
        for (auto body2 = bodies_.begin(); body2 != bodies_.end(); ++body2) {
            if (body1 == body2) {
                continue;
            }

            Vec2 delta{};
            Vec2 delta_normalized{};

            delta.x = (*body1).getPosition().x - (*body2).getPosition().x;
            delta.y = (*body1).getPosition().y - (*body2).getPosition().y;

            double distance = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));

            if (distance < (*body1).getRadius() + (*body2).getRadius())
                continue;

            delta_normalized.x = delta.x / distance;
            delta_normalized.y = delta.y / distance;

            double force = GRAVITATIONAL_CONSTANT * ((*body1).getMass() * (*body2).getMass()) / distance;

            (*body2).addForce({.x = delta_normalized.x * force, .y = delta_normalized.y * force});
            (*body1).addForce({.x = -delta_normalized.x * force, .y = -delta_normalized.y * force});
        }
    }

    for (auto& body : bodies_) {
        body.leapfrogStep(delta_time_);
    }
}

Simulation::Simulation()
{
    bodies_.emplace_back(Vec2{.x = 200, .y = 500}, 200000000, 20);
    bodies_.emplace_back(Vec2{.x = 800, .y = 500}, 200000000, 20);

    for (auto body1 = bodies_.begin(); body1 != bodies_.end(); ++body1) {
        for (auto body2 = bodies_.begin(); body2 != bodies_.end(); ++body2) {
            if (body1 == body2) {
                continue;
            }

            Vec2 delta{};
            Vec2 delta_normalized{};

            delta.x = (*body1).getPosition().x - (*body2).getPosition().x;
            delta.y = (*body1).getPosition().y - (*body2).getPosition().y;

            double distance = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));

            if (distance < (*body1).getRadius() + (*body2).getRadius())
                continue;

            delta_normalized.x = delta.x / distance;
            delta_normalized.y = delta.y / distance;

            double force = GRAVITATIONAL_CONSTANT * ((*body1).getMass() * (*body2).getMass()) / distance;

            (*body2).bootstrapVelocity({.x = delta_normalized.x * force, .y = delta_normalized.y * force}, delta_time_);
            (*body1).bootstrapVelocity({.x = -delta_normalized.x * force, .y = -delta_normalized.y * force},
                                       delta_time_);
        }
    }
}

const std::vector<Body>& Simulation::getBodies()
{
    return bodies_;
}
