#pragma once

#include <vector>

#include <glm/ext/vector_double2.hpp>

#include "aabb.hpp"
#include "circle.hpp"

constexpr double GRAVITATIONAL_CONSTANT = 0.0000000000667430;
constexpr double TIMESTEP = 1.0 / 60.0;

class Simulation
{
  private:
    std::vector<Circle> bodies_;

    AABoundingBox area_{glm::dvec2(0.0, 0.0), 20, 20};

    void processBoundaryConstraint(Circle& body);
    void processBodyCollisions();

  public:
    void tick();

    void addBody(Circle body);
    void addRandomBodies(unsigned int count);

    const AABoundingBox& getBoundingBox();

    const std::vector<Circle>& getBodies() const noexcept;
};
