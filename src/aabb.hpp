#pragma once

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_double4.hpp>
#include <raylib.h>

#include "body.hpp"

using CrossingError = struct CrossingError {
    double top{};
    double bottom{};
    double left{};
    double right{};
};

class AABoundingBox
{
  private:
    glm::dvec2 position_{};

    double width_{};
    double height_{};

  public:
    AABoundingBox(glm::dvec2 position, double width, double height);
    bool isCollidingAABB(const AABoundingBox& other);

    CrossingError findBodyCrossingError(const Body& body);

    void debugDraw(Color color) const noexcept;

    void setPosition(glm::dvec2 position);
    void setWidth(double width);
    void setHeight(double height);

    glm::dvec2 getPosition() const noexcept;
    double getWidth() const noexcept;
    double getHeight() const noexcept;
};
