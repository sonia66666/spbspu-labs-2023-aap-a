#include "rectangle.hpp"
#include <stdexcept>

nikitov::Rectangle::Rectangle(point_t& leftCorner, point_t& rightCorner):
  leftCorner_(leftCorner),
  rightCorner_(rightCorner)
{
  if (leftCorner_.x >= rightCorner_.x || leftCorner_.y >= rightCorner_.x)
  {
    throw std::invalid_argument("Error: invalid rectangle arguments");
  }
}

double nikitov::Rectangle::getArea()
{
  return (rightCorner_.x - leftCorner_.x) * (rightCorner_.y - leftCorner_.y);
}

nikitov::rectangle_t nikitov::Rectangle::getFrameRect()
{
  double width = rightCorner_.x - leftCorner_.x;
  double height = rightCorner_.y - leftCorner_.y;
  point_t center = { leftCorner_.x + width / 2, leftCorner_.y + height / 2 };
  return { width, height, center };
}

void nikitov::Rectangle::move(const point_t& point)
{
  point_t center = getFrameRect().pos;
  double dx = point.x - center.x;
  double dy = point.y - center.y;
  move(dx, dy);
}

void nikitov::Rectangle::move(double dx, double dy)
{
  leftCorner_.x += dx;
  leftCorner_.y += dy;
  rightCorner_.x += dx;
  rightCorner_.y += dy;
}

void nikitov::Rectangle::scale(double ratio)
{
  point_t center = getFrameRect().pos;
  leftCorner_.x = center.x - (center.x - leftCorner_.x) * ratio;
  leftCorner_.y = center.y - (center.y - leftCorner_.y) * ratio;
  rightCorner_.x = center.x + (leftCorner_.x - center.x) * ratio;
  rightCorner_.y = center.y + (leftCorner_.y - center.y) * ratio;
}
