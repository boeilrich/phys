#pragma once

#include "main.hpp"

class Body
{
  private:
    double mass_;
    double radius_;

    Vec2 position_{};
    Vec2 velocity_{};
    Vec2 force_{};

    Vec2 calculateCurrentAcceleration();

  public:
    Body(Vec2 position, double mass, double radius);

    void leapfrogStep(double delta_time);
    void addForce(Vec2 force);
    void bootstrapVelocity(Vec2 acceleration, double delta_time);

    double getMass();
    double getRadius();
    Vec2 getPosition();
};
