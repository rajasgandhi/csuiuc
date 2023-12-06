#include "color.hpp"

#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (r < kColorValueMin || r > kColorValueMax || g < kColorValueMin ||
      g > kColorValueMax || b < kColorValueMin || b > kColorValueMax) {
    throw std::runtime_error("invalid arguments");
  }

  red_ = r;
  green_ = g;
  blue_ = b;
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}