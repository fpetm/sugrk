#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <stdio.h>
#include "threadpool.hpp"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "image.hpp"
#include "log.hpp"
#include <thread>
#include "raytracer.hpp"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "log.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1900) &&                                 \
    !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See
// 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif
namespace sugrk {
class Window {
public:
  Window() : m_ThreadPool(10) {}
  void Init(int width = 1280, int height = 720);
  bool Update(RayTracerConfig &conf, Scene &scene, RayTracer<RGBA8> &raytracer);
  void Stop();

  void SetBuffer(std::shared_ptr<Image<RGBA8>> render_buffer) {
    m_RenderBuffer = render_buffer;
  }

private:
  std::shared_ptr<Image<RGBA8>> m_RenderBuffer;
  ThreadPool m_ThreadPool;
  GLFWwindow *m_Window;
  ImVec4 m_ClearColor;
  int m_Width, m_Height;
};
} // namespace sugrk
