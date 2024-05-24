#pragma once
#include "image.hpp"
#include "scene.hpp"
#include <unistd.h>

namespace sugrk {
struct RayTracerConfig {
  int width, height;
  float blue;
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
              RayTracerConfig config) {
    {
      std::lock_guard<std::mutex> guard(m_StopMutex);
      m_Stop = false;
    }
    if (!(render_buffer->Width() == config.width &&
          render_buffer->Height() == config.height)) {
      render_buffer->Initialize(config.width, config.height);
    }

    m_Rendering = true;
    for (int x = 0; x < config.width; x++) {
      for (int y = 0; y < config.height; y++) {
        {
          std::lock_guard<std::mutex> lock(m_StopMutex);
          if (m_Stop) {
            m_Rendering = false;
            break;
          }
        }
        const RGBA8 color((1 - (double)x / config.width) * 255.0,
                          (double)y / config.height * 255.0, config.blue * 255,
                          255);
        render_buffer->Set(x, y, color);
        usleep(10);
      }
      if (!m_Rendering) {
        break;
      }
    }
      
    SG_INFO("Rendering done");
    m_Rendering = false;
  }
};
} // namespace sugrk
