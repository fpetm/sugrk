#include "raytracer.hpp"
#include "color.hpp"
#include "util.hpp"
#include <Eigen/Dense>

namespace sugrk {
  RayTracerConfig::RayTracerConfig() {
    width = 300;
    height = 200;
    focal_length = 1;
    viewport_height = 2;
  }

  float hit_sphere(const Vec3 &center, float radius, const Ray &r) {
    Vec3 oc = center - r.Origin();
    const float a = r.Direction().dot(r.Direction());
    const float h = r.Direction().dot(oc);
    const float c = oc.dot(oc) - radius * radius;
    const float discriminant = h*h - a*c;

    if (discriminant < 0)
      return -1.0f;
    else
      return (h - sqrtf(discriminant))/ a;
  }

  template <typename color_t>
  color_t ray_color(const Ray &r, const Scene &world) {
    HitRecord rec;
    if (world.Hit(r, 0, INFINITY, rec)) {
      return RGBAf(Vec3(0.5*(rec.normal+Vec3(1,1,1))));
    }

    Vec3 unit_direction = r.Direction().normalized();
    float a = 0.5f*(unit_direction.y() + 1.0f);
    return lerp<RGBAf>(RGBAf(0.5f, 0.7f, 1.0f, 1.0f), RGBAf(1.0f, 1.0f, 1.0f, 1.0f), a);
  }

  template <typename color_t>
  void RayTracer<color_t>::Render(std::shared_ptr<Image<color_t>> render_buffer, Scene &scene, RayTracerConfig config) {
    {
      std::lock_guard<std::mutex> guard(m_StopMutex);
      m_Stop = false;
    }
    if (!(render_buffer->Width() == config.width &&
          render_buffer->Height() == config.height)) {
      render_buffer->Initialize(config.width, config.height);
    }

    m_Rendering = true;

    const float aspect_ratio = (double)config.width / config.height;
    const float focal_length = config.focal_length;
    const float viewport_height = config.viewport_height;
    const float viewport_width = viewport_height * aspect_ratio;
    const Vec3 camera_center(0,0,0);
    const Vec3 viewport_u(viewport_width, 0, 0);
    const Vec3 viewport_v(0, -viewport_height, 0);
    const Vec3 pixel_delta_u = viewport_u / config.width;
    const Vec3 pixel_delta_v = viewport_v / config.height;
    const Vec3 viewport_upper_left = camera_center - Eigen::Vector3f(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    const Vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    int samples_per_pixel = config.samples_per_pixel;

    SG_INFO("Starting rendering");
  for (int y = 0; y < config.height; y++) {
    for (int x = 0; x < config.width; x++) {
        {
          std::lock_guard<std::mutex> lock(m_StopMutex);
          if (m_Stop) {
            m_Rendering = false;
            break;
          }
        }
        RGBAf color(0.0, 0.0, 0.0, 1.0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          Vec3 offset(random_float() - 0.5f, random_float() - 0.5f, 0.0);
          Vec3 pixel_sample = pixel00_loc + ((x+offset.x()) * pixel_delta_u) + ((y+offset.y()) * pixel_delta_v);
          Vec3 origin(0,0,0);
          Vec3 ray_direction = pixel_sample - origin;
          Ray ray(origin, ray_direction);
          color += ray_color<RGBAf>(ray, scene);
        }
        color *= 1.0f/float(samples_per_pixel);
        render_buffer->Set(x, y, color);
      }
      if (!m_Rendering) {
        break;
      }
    }


      
    SG_INFO("Rendering done");
    m_Rendering = false;
  }

  void tmp() {
    Scene sc;
  RayTracer<RGBA8> r1;
  RayTracer<RGBAf> r2;
  r1.Render(nullptr, sc, {});
  r2.Render(nullptr, sc, {});
  }
}
