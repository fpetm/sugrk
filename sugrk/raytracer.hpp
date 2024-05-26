#pragma once
#include "image.hpp"
#include "util.hpp"
#include "scene.hpp"
#include <unistd.h>

namespace sugrk {
  typedef Eigen::Vector3f Vec3;
struct RayTracerConfig {
  int width, height;
  float focal_length;
  float viewport_height;
  int samples_per_pixel;
  RayTracerConfig();
};

  class Ray {
    public:
      Ray();
      Ray(const Vec3 &origin, const Vec3 &direction) : m_Origin(origin), m_Direction(direction) {}
      Vec3 Origin() const { return m_Origin; }
      Vec3 Direction() const { return m_Direction; }
      Vec3 at(double t) const { return m_Origin + t * m_Direction; }
    private:
      Vec3 m_Origin, m_Direction;
  };
class HitRecord {
  public:
    Vec3 position, normal;
    bool front_face;
    float t;

    void SetFaceNormal(const Ray& ray, const Vec3 &outward_normal) {
      front_face = ray.Direction().dot(outward_normal) < 0;
      normal = front_face ? outward_normal : - outward_normal;
    }
};
class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& ray, float ray_tmin, float ray_tmax, HitRecord &record) const = 0;
};

  class Sphere : public Hittable {
    public:
      Vec3 m_Center;
      float m_Radius;

    Sphere(const Vec3 &center, float radius) : m_Center(center), m_Radius(fmax(0.0f, radius)) {}

    bool Hit(const Ray& r, float ray_tmin, float ray_tmax, HitRecord &record) const override {
    Vec3 oc = m_Center - r.Origin();
    const float a = r.Direction().dot(r.Direction());
    const float h = r.Direction().dot(oc);
    const float c = oc.dot(oc) - m_Radius * m_Radius;
    const float discriminant = h*h - a*c;
    if (discriminant < 0) return false;
    const float sqrtd = sqrtf(discriminant);
    float root = (h-sqrtd)/a;
    if (root <= ray_tmin || ray_tmax <= root) {
      root = (h + sqrtd)/a;
      if (root <= ray_tmin || ray_tmax <= root) {
        return false;
      }
    }
    record.t = root;
    record.position = r.at(record.t);
    Vec3 outward_normal = (record.position - m_Center) / m_Radius;
    record.SetFaceNormal(r, outward_normal);
    return true;
    }
  };

  class Scene : public Hittable {
    public:
      std::vector<std::shared_ptr<Hittable>> m_Objects;

      Scene() {
      }

      void Add(std::shared_ptr<Hittable> object) {
        m_Objects.push_back(object);
      }

      bool Hit(const Ray &r, float ray_tmin, float ray_tmax, HitRecord &record) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto &object : m_Objects) {
          if (object->Hit(r, ray_tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            record = temp_rec;
          }
        }

        return hit_anything;
      }
  };

template <typename color_t>
class RayTracer {
private:
  bool m_Rendering;
  bool m_Stop;
  std::mutex m_StopMutex;
public:
  bool Rendering() { return m_Rendering; }
  void Stop() {
      std::lock_guard<std::mutex> guard(m_StopMutex);
      m_Stop = true;
  }

  void Render(std::shared_ptr<Image<color_t>> render_buffer, Scene &scene,
              RayTracerConfig config);
};
} // namespace sugrk
