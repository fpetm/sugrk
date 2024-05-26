#pragma once
#include <Eigen/Dense>
#include <random>

namespace sugrk {
  typedef Eigen::Vector3f Vec3;
  typedef Eigen::Vector4f Vec4;

  const float Infinity = std::numeric_limits<float>::infinity();

  template <typename T>
  inline T lerp(T a, T b, float c) {
    return (a * c) + (b * (1-c));
  }

  template <typename T>
  class Interval {
    private:
      T m_A, m_B;
    public:
      Interval<float>() : m_A(+Infinity), m_B(-Infinity) {}

      Interval(T a, T b) : m_A(a), m_B(b) {}
      bool Contains(T c) const { return c >= m_A && c <= m_B; }
      bool Surrounds(T c) const {return c > m_A && c < m_B; }
      T A() const { return m_A; }
      T B() const { return m_B; }
      T clamp(T c) const { return std::max(A(), std::min(B(), c)); }
  };
  typedef Interval<float> Intervalf;

  inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
  }

  inline float random_float(float a, float b) {
    return lerp<float>(a, b, random_float());
  }
}
