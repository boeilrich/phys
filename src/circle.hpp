#pragma once

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_double3.hpp>
#include <raylib.h>

class Circle
{
  private:
    double mass_;
    double radius_;

    Color color_{};

    glm::dvec2 position_{};
    glm::dvec2 velocity_{};
    glm::dvec2 accumulated_acceleration_{};

  public:
    Circle(glm::dvec2 position, double mass, double radius, glm::dvec3 color)
        : mass_(mass),
          radius_(radius),
          position_(position)
    {
        Vector4 c = {.x = static_cast<float>(color.r),
                     .y = static_cast<float>(color.g),
                     .z = static_cast<float>(color.b),
                     .w = 1.0};
        color_ = ColorFromNormalized(c);
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

    Color getColor() const noexcept;
};
