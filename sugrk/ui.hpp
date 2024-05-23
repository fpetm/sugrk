#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "log.hpp"
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
    void Init(int width = 1280, int height = 720);
    bool Update();
    void Stop();
    private:
    GLFWwindow* m_Window;
    ImVec4 m_ClearColor;
    int m_Width, m_Height;
  };
}
