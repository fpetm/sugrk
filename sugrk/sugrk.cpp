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
  RayTracerConfig conf;
  std::shared_ptr<Image<RGBA8>> render_buffer =
      std::make_shared<Image<RGBA8>>(conf.width, conf.height);
  Scene scene;
  scene.Add(std::make_shared<Sphere>(Vec3(0,0,-1), 0.5));
  scene.Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));
  wnd.SetBuffer(render_buffer);

  while (wnd.Update(conf, scene, raytracer)) {}

  wnd.Stop();

  return 0;
}
