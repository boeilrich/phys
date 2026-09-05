#pragma once

#include <glm/ext/vector_double2.hpp>

class Body
{
  private:
    double mass_;
    double radius_;

    glm::dvec2 position_{};
    glm::dvec2 velocity_{};
    glm::dvec2 accumulated_acceleration_{};

  public:
    Body(glm::dvec2 position, double mass, double radius) : mass_(mass), radius_(radius), position_(position)
    {
    }

    void tick(double dt);
    void applyAcceleration(glm::dvec2 acceleration);
    void applyForce(glm::dvec2 force);

    void setVelocity(glm::dvec2 velocity);
    void setPosition(glm::dvec2 position);

    double getMass() const noexcept;
    double getRadius() const noexcept;
    glm::dvec2 getPosition() const noexcept;
    glm::dvec2 getVelocity() const noexcept;
};
