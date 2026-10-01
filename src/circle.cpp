#include "circle.hpp"

#include <glm/ext/vector_double2.hpp>
#include <raylib.h>

void Circle::tick(double dt)
{
    velocity_ += accumulated_acceleration_ * dt;
    accumulated_acceleration_ = {};

    position_ += velocity_ * dt;
}

void Circle::applyAcceleration(glm::dvec2 acceleration)
{
    accumulated_acceleration_ += acceleration;
}

void Circle::applyForce(glm::dvec2 force)
{
    accumulated_acceleration_ += force / mass_;
}

void Circle::setVelocity(glm::dvec2 velocity)
{
    velocity_ = velocity;
}

void Circle::setPosition(glm::dvec2 position)
{
    position_ = position;
}

double Circle::getMass() const noexcept
{
    return mass_;
}

double Circle::getRadius() const noexcept
{
    return radius_;
}

glm::dvec2 Circle::getPosition() const noexcept
{
    return position_;
}

glm::dvec2 Circle::getVelocity() const noexcept
{
    return velocity_;
}

Color Circle::getColor() const noexcept
{
    return color_;
}
