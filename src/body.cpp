#include "body.hpp"

#include <glm/ext/vector_double2.hpp>

void Body::tick(double dt)
{
    velocity_ += accumulated_acceleration_ * dt;
    accumulated_acceleration_ = {};

    position_ += velocity_ * dt;
}

void Body::applyAcceleration(glm::dvec2 acceleration)
{
    accumulated_acceleration_ += acceleration;
}

void Body::applyForce(glm::dvec2 force)
{
    accumulated_acceleration_ += force / mass_;
}

void Body::setVelocity(glm::dvec2 velocity)
{
    velocity_ = velocity;
}

void Body::setPosition(glm::dvec2 position)
{
    position_ = position;
}

double Body::getMass() const noexcept
{
    return mass_;
}

double Body::getRadius() const noexcept
{
    return radius_;
}

glm::dvec2 Body::getPosition() const noexcept
{
    return position_;
}

glm::dvec2 Body::getVelocity() const noexcept
{
    return velocity_;
}
