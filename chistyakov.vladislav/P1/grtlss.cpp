#include "grtlss.hpp"
#include <limits>
#include <stdexcept>

chistyakov::GrtLss::GrtLss() :
  fstNum_(0),
  midNum_(0),
  counter_(0),
  isSecuenceOk_(false)
{}

void chistyakov::GrtLss::operator()(int number)
{
  if (!fstNum_)
  {
    fstNum_ = number;
  }
  else if (!midNum_)
  {
    midNum_ = number;
  }
  else
  {
    if (!isSecuenceOk_)
    {
      isSecuenceOk_ = true;
    }

    if (fstNum_ > midNum_ and midNum_ > number)
    {
      size_t max_size = std::numeric_limits< size_t >::max();
      if (counter_ == max_size)
      {
        throw std::logic_error("sequence is too long");
      }
      else
      {
        ++counter_;
      }
    }
    fstNum_ = midNum_;
    midNum_ = number;
  }
}

size_t chistyakov::GrtLss::operator()() const
{
  if (!isSecuenceOk_)
  {
    throw std::invalid_argument("sequence is too short");
  }
  else
  {
    return counter_;
  }
}
