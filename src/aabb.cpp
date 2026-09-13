#include "aabb.hpp"

#include <glm/ext/vector_double2.hpp>
#include <glm/ext/vector_double4.hpp>
#include <raylib.h>

#include "body.hpp"
#include "util.hpp"

AABoundingBox::AABoundingBox(glm::dvec2 position, double width, double height)
    : position_(position),
      width_(width),
      height_(height) {};

bool AABoundingBox::isCollidingAABB(const AABoundingBox& other)
{
    return (position_.x - width_ / 2.0 <= other.position_.x + other.width_ / 2.0) &&
           (position_.x + width_ / 2.0 >= other.position_.x - other.width_ / 2.0) &&
           (position_.y - height_ / 2.0 <= other.position_.y + other.height_ / 2.0) &&
           (position_.y + height_ / 2.0 >= other.position_.y - other.height_ / 2.0);
}

CrossingError AABoundingBox::findBodyCrossingError(const Body& body)
{
    const auto position = body.getPosition();
    const auto radius = body.getRadius();

    CrossingError error{};

    error.top = (position.y + radius) - (position_.y + height_ / 2.0);     // top side
    error.bottom = (position_.y - height_ / 2.0) - (position.y - radius);  // bottom side
    error.left = (position_.x - width_ / 2.0) - (position.x - radius);     // left side
    error.right = (position.x + radius) - (position_.x + width_ / 2.0);    // right side

    return error;
}

void AABoundingBox::debugDraw(Color color) const noexcept
{
    glm::dvec2 topLeft = worldToScreen(glm::dvec2(position_.x - width_ / 2.0, position_.y + height_ / 2.0));

    DrawRectangleLines(static_cast<int>(topLeft.x), static_cast<int>(topLeft.y),
                       static_cast<int>(width_ * PIXELS_PER_METER), static_cast<int>(height_ * PIXELS_PER_METER),
                       color);

    glm::dvec2 position = worldToScreen(position_);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 2, BLUE);
}

void AABoundingBox::setPosition(glm::dvec2 position)
{
    position_ = position;
}

void AABoundingBox::setWidth(double width)
{
    width_ = width;
}

void AABoundingBox::setHeight(double height)
{
    height_ = height;
}

glm::dvec2 AABoundingBox::getPosition() const noexcept
{
    return position_;
}

double AABoundingBox::getWidth() const noexcept
{
    return width_;
}

double AABoundingBox::getHeight() const noexcept
{
    return height_;
}
