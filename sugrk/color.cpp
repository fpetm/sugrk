#include "color.hpp"

namespace sugrk::color {
  RGBAf operator+(RGBAf a) const;
  RGBAf operator-(RGBAf a) const;
  RGBAf operator*(float a) const;
  RGBAf operator+=(RGBAf a);
  RGBAf operator-=(RGBAf a);
  RGBAf operator*(float a);
}

