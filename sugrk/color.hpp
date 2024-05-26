#pragma once
#include "log.hpp"
#include <cstdint>
#include <Eigen/Dense>

namespace sugrk {
class Color {
public:
  virtual ~Color() = default;
};

class RGBAf : public Color {
public:
  float R, G, B, A;
  RGBAf() : R(1.0f), G(0.0f), B(1.0f), A(1.0f) {}
  RGBAf(float r, float g, float b, float a) : R(std::min(1.0f, r)), G(std::min(1.0f, g)), B(std::min(1.0f, b)), A(std::min(1.0f, a)) {}
  ~RGBAf() {}

  RGBAf(const Eigen::Vector3f v, float a = 1.0f) :
    R(v.x()), G(v.y()), B(v.z()), A(a)
  {}

  RGBAf(const Eigen::Vector4f v) :
    R(v.x()), G(v.y()), B(v.z()), A(v.w())
  {}

  operator Eigen::Vector4f() {
    return Eigen::Vector4f(R,G,B,A);
  }
  operator Eigen::Vector3f() {
    return Eigen::Vector3f(R,G,B);
  }

  RGBAf operator+(RGBAf a) const;
  RGBAf operator-(RGBAf a) const;
  RGBAf operator*(float a) const;
  void operator+=(RGBAf a);
  void operator-=(RGBAf a);
  void operator*=(float a);
};

class RGBA8 : public Color {
public:
  RGBA8() : R(255), G(0), B(255), A(255) {}
  RGBA8(const RGBAf &r) {
    R = r.R * 255;
    G = r.G * 255;
    B = r.B * 255;
    A = r.A * 255;
  }
  RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {}
  ~RGBA8() {}
  uint8_t R, G, B, A;

  operator RGBAf() const {
    return RGBAf(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f);
  }
};
}; // namespace sugrk
