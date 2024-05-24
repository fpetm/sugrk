#include "raytracer.hpp"
#include "color.hpp"

#if 0
namespace sugrk {
  template <typename color_t>
  void RayTracer<color_t>::Render(std::shared_ptr<Image<color_t>> render_buffer, Scene &scene, RayTracerConfig config) {
    // Replace render_buffer if size does not match
    if (!(render_buffer->Width() == config.width &&
          render_buffer->Height() == config.height)) {
      render_buffer->Initalize(config.width, config.height);
    }

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
}
#endif
