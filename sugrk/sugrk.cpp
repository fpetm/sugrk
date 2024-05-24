#include "image.hpp"
#include "log.hpp"
#include "ui.hpp"

using namespace sugrk;

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

constexpr int g_RenderWidth = 300;
constexpr int g_RenderHeight = 200;

int main(int, char **) {
  sugrk::Log::Init();
  SG_INFO("Hello");
  sugrk::Window wnd;
  wnd.Init(800, 600);
  RayTracer<RGBA8> raytracer;
  RayTracerConfig conf = {300, 200, 0.1};
  Scene scene = {};
  std::shared_ptr<Image<RGBA8>> render_buffer =
      std::make_shared<Image<RGBA8>>(conf.width, conf.height);
  wnd.SetBuffer(render_buffer);

  while (wnd.Update(conf, scene, raytracer)) {
  }

  wnd.Stop();

  return 0;
}
