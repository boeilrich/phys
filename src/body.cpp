#include "body.hpp"

#include "main.hpp"

Body::Body(Vec2 position, double mass, double radius) : mass_(mass), radius_(radius), position_(position)
{
}

Vec2 Body::calculateCurrentAcceleration()
{
    Vec2 acceleration{};

    acceleration.x = force_.x / mass_;
    acceleration.y = force_.y / mass_;

    return acceleration;
}

void Body::leapfrogStep(double delta_time)
{
    Vec2 acceleration = calculateCurrentAcceleration();
    force_.x = 0;
    force_.y = 0;

    velocity_.x = velocity_.x + acceleration.x * delta_time;
    velocity_.y = velocity_.y + acceleration.y * delta_time;

    position_.x = position_.x + velocity_.x * delta_time;
    position_.y = position_.y + velocity_.y * delta_time;
}

void Body::addForce(Vec2 force)
{
    force_.x += force.x;
    force_.y += force.y;
}

void Body::bootstrapVelocity(Vec2 acceleration, double delta_time)
{
    velocity_.x = acceleration.x * delta_time / 2;
    velocity_.y = acceleration.y * delta_time / 2;
}

double Body::getMass()
{
    return mass_;
}

double Body::getRadius()
{
    return radius_;
}

Vec2 Body::getPosition()
{
    return position_;
}
