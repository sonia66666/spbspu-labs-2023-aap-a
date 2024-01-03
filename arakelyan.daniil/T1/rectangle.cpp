#include "rectangle.hpp"
#include "base-types.hpp"
#include <stdexcept>

Rectangle::Rectangle(point_t fp, point_t sp):
  pointRightUp_(fp),
  pointLeftDown_(sp),
  midpoint_{((pointRightUp_.x_ + pointLeftDown_.x_) / 2), ((pointRightUp_.y_ + pointLeftDown_.y_) / 2)}
{
  //добавить проверку на координаты, их положение относительно углов
};

Rectangle::~Rectangle()
{};

double Rectangle::getArea() const
{
  double width = pointRightUp_.x_ - pointLeftDown_.x_;
  double height = pointRightUp_.y_ - pointLeftDown_.y_;
  return width * height;
}

rectangle_t Rectangle::getFrameRect()
{
  double width = pointRightUp_.x_ - pointLeftDown_.x_;
  double height = pointRightUp_.y_ - pointLeftDown_.y_;
  rectangle_t data = {width, height, midpoint_};
  return data;
};

void Rectangle::move(double delX, double delY)
{
  pointLeftDown_.x_ += delX;
  pointLeftDown_.y_ += delY;
  pointRightUp_.x_ += delX;
  pointRightUp_.y_ += delY;
  midpoint_.x_ += delX;
  midpoint_.y_ += delY;
}

void Rectangle::move(point_t point)
{
  double width = pointRightUp_.x_ - pointLeftDown_.x_;
  double height = pointRightUp_.y_ - pointLeftDown_.y_;
  pointRightUp_.x_ = point.x_ + width;
  pointRightUp_.y_ = point.y_ + height;
  pointLeftDown_.x_ = point.x_ + width;
  pointLeftDown_.y_ = point.y_ + height;
  midpoint_.x_ = (pointRightUp_.x_ + pointLeftDown_.x_) / 2;
  midpoint_.y_ = (pointRightUp_.y_ + pointLeftDown_.y_) / 2;
}

void Rectangle::scale(double k)
{
  if (k < 0.0)
  {
    throw std::logic_error("the coefficient cannot be less than zero!");
  }
  double width = pointRightUp_.x_ - pointLeftDown_.x_;
  double height = pointRightUp_.y_ - pointLeftDown_.y_;
  double widthWithScale = width * k;
  double heightWithScale = height * k;
  double widthHalf = widthWithScale / 2;
  double heightHalf = heightWithScale / 2;
  pointLeftDown_.x_ = midpoint_.x_ - widthHalf;
  pointLeftDown_.y_ = midpoint_.y_ - heightHalf;
  pointRightUp_.x_ = midpoint_.x_ + widthHalf;
  pointRightUp_.y_ = midpoint_.y_ + heightHalf;
}
