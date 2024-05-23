find_package(OpenGL REQUIRED)
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/extern/imgui/")
set(IMGUI_SRCS "${IMGUI_DIR}/imgui.cpp" "${IMGUI_DIR}/imgui_demo.cpp" "${IMGUI_DIR}/imgui_draw.cpp" "${IMGUI_DIR}/imgui_tables.cpp" "${IMGUI_DIR}/imgui_widgets.cpp" "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp" "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")

add_executable(sugrk sugrk.cpp log.cpp ui.cpp ${IMGUI_SRCS})

target_include_directories(sugrk SYSTEM PUBLIC  "../extern/eigen")
target_include_directories(sugrk SYSTEM PUBLIC  "../extern/imgui")
target_include_directories(sugrk SYSTEM PUBLIC  "../extern/stb")
target_link_libraries(sugrk PUBLIC spdlog::spdlog glfw OpenGL::GL)
