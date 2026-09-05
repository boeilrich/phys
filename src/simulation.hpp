#pragma once

#include <vector>

#include "body.hpp"

constexpr double GRAVITATIONAL_CONSTANT = 0.0000000000667430;

class Simulation
{
  private:
    const double delta_time_ = 1.0 / 60.0;
    std::vector<Body> bodies_;

  public:
    void tick();

    Simulation(unsigned long body_count);
};
