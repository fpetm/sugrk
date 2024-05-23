#include "ui.hpp"
namespace sugrk {
  static void glfw_error_callback(int error, const char *description) {
    SG_ERROR("GLFW Error {}: {}", error, description);
  }
  void Window::Init(int width, int height) {
    m_Width = width; m_Height = height;
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
      SG_CRITICAL("Failed to initalize GLFW!");
      return;
    }
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char *glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
  m_Window = glfwCreateWindow(m_Width, m_Height, "sugrk", nullptr, nullptr);

  if (m_Window == nullptr) {
    SG_CRITICAL("Failed to create window");
  }

  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
#ifdef __EMSCRIPTEN__
  ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
  ImGui_ImplOpenGL3_Init(glsl_version);

  io.Fonts->AddFontFromFileTTF("resources/fonts/Roboto-Medium.ttf", 14.0f);

  m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  }

  bool Window::Update() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();
    glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
    glViewport(0, 0, m_Height, m_Height);
    glClearColor(m_ClearColor.x * m_ClearColor.w, m_ClearColor.y * m_ClearColor.w,
                 m_ClearColor.z * m_ClearColor.w, m_ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_Window);
    return !glfwWindowShouldClose(m_Window);
  }

  void Window::Stop() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(m_Window);
  glfwTerminate();
  }
}
