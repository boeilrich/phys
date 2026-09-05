#include "simulation.hpp"

#include <vector>

#include "body.hpp"
#include "main.hpp"

void Simulation::tick()
{
    for (auto& body : bodies_) {
        body.applyAcceleration(Vec2{.x = 0, .y = -9.81});
    }

    for (auto& body : bodies_) {
        body.tick();

        double radius = body.getRadius();
        Vec2 position = body.getPosition();

        if (position.y - radius < 0) {
            Vec2 velocity = body.getVelocity();
            velocity.y = -velocity.y * 0.8;
            body.setVelocity(velocity);
            position.y = 0 + radius;
            body.setPosition(position);
        }
    }
}

void Simulation::addBody(Body body)
{
    bodies_.push_back(body);
}

const std::vector<Body>& Simulation::getBodies() const noexcept
{
    return bodies_;
}
