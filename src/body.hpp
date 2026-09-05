#pragma once

#include "main.hpp"

class Body
{
  private:
    double mass_;
    double radius_;

    Vec2 position_{};
    Vec2 velocity_{};

    Vec2 accumulated_acceleration_{};

  public:
    Body(Vec2 position, double mass, double radius);

    void tick();
    void applyAcceleration(Vec2 acceleration);
    void applyForce(Vec2 force);

    void setVelocity(Vec2 velocity);
    void setPosition(Vec2 position);

    double getMass() const noexcept;
    double getRadius() const noexcept;
    Vec2 getPosition() const noexcept;
    Vec2 getVelocity() const noexcept;
};
