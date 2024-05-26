#include "color.hpp"

namespace sugrk {
  RGBAf RGBAf::operator+(RGBAf a) const {
    return RGBAf(R + a.R, G + a.G, B + a.B, A + a.A);
  }
  RGBAf RGBAf::operator-(RGBAf a) const {
    return RGBAf(R - a.R, G - a.G, B - a.B, A - a.A);
  }
  RGBAf RGBAf::operator*(float a) const {
    return RGBAf(R * a, G * a, B * a, A * a);
  }
  void RGBAf::operator+=(RGBAf a) {
    R += a.R;
    G += a.G;
    B += a.B;
    A += a.A;
  }
  void RGBAf::operator-=(RGBAf a) {
    R -= a.R;
    G -= a.G;
    B -= a.B;
    A -= a.A;
  }
  void RGBAf::operator*=(float a) {
    R *= a;
    G *= a;
    B *= a;
    A *= a;
  }
}

