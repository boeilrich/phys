#pragma once

#include <vector>

#include "body.hpp"

constexpr double GRAVITATIONAL_CONSTANT = 0.0000000000667430;
constexpr double TIMESTEP = 1.0 / 60.0;

class Simulation
{
  private:
    std::vector<Body> bodies_;

  public:
    void tick();

    void addBody(Body body);

    const std::vector<Body>& getBodies() const noexcept;
};
