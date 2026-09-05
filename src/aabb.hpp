#pragma once

#include <optional>

#include <glm/ext/vector_double2.hpp>
#include <raylib.h>

#include "body.hpp"

enum Side {
    Top,
    Bottom,
    Left,
    Right,
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
    std::optional<Side> findBodyCrossingSide(const Body& body);

    void debugDraw(Color color) const noexcept;

    void setPosition(glm::dvec2 position);
    void setWidth(double width);
    void setHeight(double height);

    glm::dvec2 getPosition() const noexcept;
    double getWidth() const noexcept;
    double getHeight() const noexcept;
};
