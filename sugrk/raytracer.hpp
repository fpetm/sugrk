#pragma once
#include "image.hpp"
namespace sugrk {
struct RayTracerConfig {
  int width, height;
  float blue;
};
class Scene {
public:
  Scene() {}
};

template <typename color_t,
          std::enable_if_t<std::is_base_of<Color, color_t>::value> * = nullptr>
class RayTracer {
public:
  void Render(std::shared_ptr<Image<color_t>> render_buffer, Scene &scene,
              RayTracerConfig config) {
    SG_INFO("Rendering ({}x{})...", config.width, config.height);
    // Replace render_buffer if size does not match
    if (!(render_buffer->Width() == config.width &&
          render_buffer->Height() == config.height)) {
      render_buffer.reset();
      render_buffer =
          std::make_shared<Image<color_t>>(config.width, config.height);
    }

    SG_INFO("{}", config.blue);
    for (int x = 0; x < config.width; x++) {
      for (int y = 0; y < config.height; y++) {
        const RGBA8 color((1 - (double)x / config.width) * 255.0,
                          (double)y / config.height * 255.0, config.blue * 255,
                          255);
        render_buffer->Set(x, y, color);
      }
    }
    render_buffer->UpdateTexture();
  }
};
} // namespace sugrk
