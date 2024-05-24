#pragma once
#include "log.hpp"
#include <cstdint>

namespace sugrk {
class Color {
public:
  virtual ~Color() = default;
};

class RGBAf : public Color {
public:
  float R, G, B, A;
  RGBAf() : R(1.0f), G(0.0f), B(1.0f), A(1.0f) {}
  RGBAf(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}
  ~RGBAf() {}
};

class RGBA8 : public Color {
public:
  RGBA8() : R(255), G(0), B(255), A(255) {}
  RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {}
  ~RGBA8() {}
  uint8_t R, G, B, A;

  operator RGBAf() {
    return RGBAf(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f);
  }
};
}; // namespace sugrk
