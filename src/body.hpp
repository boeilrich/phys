#pragma once

#include "main.hpp"

class Body
{
  private:
    double mass_;

    Vec2 position_{};
    Vec2 velocity_{};
    Vec2 force_{};

    Vec2 calculateCurrentAcceleration();

  public:
    void leapfrogStep(double delta_time);
    void addForce(Vec2 force);
    void bootstrapVelocity(Vec2 acceleration, double delta_time);

    double getMass();
    Vec2 getPosition();
};
