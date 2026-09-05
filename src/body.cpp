#include "body.hpp"

#include "main.hpp"
#include "simulation.hpp"

Body::Body(Vec2 position, double mass, double radius) : mass_(mass), radius_(radius), position_(position)
{
}

void Body::tick()
{
    velocity_.x += accumulated_acceleration_.x * TIMESTEP;
    velocity_.y += accumulated_acceleration_.y * TIMESTEP;

    accumulated_acceleration_.x = 0;
    accumulated_acceleration_.y = 0;

    position_.x += velocity_.x * TIMESTEP;
    position_.y += velocity_.y * TIMESTEP;
}

void Body::applyAcceleration(Vec2 acceleration)
{
    accumulated_acceleration_.x += acceleration.x;
    accumulated_acceleration_.y += acceleration.y;
}

void Body::applyForce(Vec2 force)
{
    accumulated_acceleration_.x += force.x / mass_;
    accumulated_acceleration_.y += force.y / mass_;
}

void Body::setVelocity(Vec2 velocity)
{
    velocity_ = velocity;
}

void Body::setPosition(Vec2 position)
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

Vec2 Body::getPosition() const noexcept
{
    return position_;
}

Vec2 Body::getVelocity() const noexcept
{
    return velocity_;
}
