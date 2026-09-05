#include "aabb.hpp"

#include <optional>

#include <glm/ext/vector_double2.hpp>
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

std::optional<Side> AABoundingBox::findBodyCrossingSide(const Body& body)
{
    const auto position = body.getPosition();
    const auto radius = body.getRadius();

    if (position.x - radius <= position_.x - width_ / 2.0) {
        return Side::Left;
    }

    if (position.x + radius >= position_.x + width_ / 2.0) {
        return Side::Right;
    }

    if (position.y - radius <= position_.y - height_ / 2.0) {
        return Side::Bottom;
    }

    if (position.y + radius >= position_.y + height_ / 2.0) {
        return Side::Top;
    }

    return std::nullopt;
}

void AABoundingBox::debugDraw(Color color) const noexcept
{
    glm::dvec2 topLeft = worldToScreen(glm::dvec2(position_.x - width_ / 2.0, position_.y + height_ / 2.0));
    glm::dvec2 topRight = worldToScreen(glm::dvec2(position_.x + width_ / 2.0, position_.y + height_ / 2.0));
    glm::dvec2 bottomLeft = worldToScreen(glm::dvec2(position_.x - width_ / 2.0, position_.y - height_ / 2.0));
    glm::dvec2 bottomRight = worldToScreen(glm::dvec2(position_.x + width_ / 2.0, position_.y - height_ / 2.0));

    DrawLine(static_cast<int>(topLeft.x), static_cast<int>(topLeft.y), static_cast<int>(topRight.x),
             static_cast<int>(topRight.y), color);
    DrawLine(static_cast<int>(topRight.x), static_cast<int>(topRight.y), static_cast<int>(bottomRight.x),
             static_cast<int>(bottomRight.y), color);
    DrawLine(static_cast<int>(topLeft.x), static_cast<int>(topLeft.y), static_cast<int>(bottomLeft.x),
             static_cast<int>(bottomLeft.y), color);
    DrawLine(static_cast<int>(bottomLeft.x), static_cast<int>(bottomLeft.y), static_cast<int>(bottomRight.x),
             static_cast<int>(bottomRight.y), color);

    glm::dvec2 position = worldToScreen(position_);

    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 2, RED);
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
