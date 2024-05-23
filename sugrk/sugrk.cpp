#include "log.hpp"
#include "ui.hpp"

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char **) {
  sugrk::Log::Init();
  SG_INFO("Hello");
  sugrk::Window wnd;
  wnd.Init(800, 600);

  while (wnd.Update()) {
  }

  wnd.Stop();

  return 0;
}
