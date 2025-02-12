#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <board.hpp>
#include <game.hpp>
#include <glfw_wrapper.hpp>
#include <imgui_wrapper.hpp>

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  bool initGraphics(int height, const char *title);

  void render();
  void shutdown();

  void newFrame();
  void finishFrame();
  void fillFrame(double r = 0, double g = 0, double b = 0, double a = 1);
  bool windowShouldClose();
  void toggleDemoWindow();
  void updateTime();
  int calculateWindowWidth(int height);
  void hookErrorCallback();
  ImVec2 GetWindowPosition(const char* windowName) {
    ImGuiWindow* window = ImGui::FindWindowByName(windowName);
    return window ? window->Pos : ImVec2(-1, -1); // Return (-1, -1) if not found
}

ImVec2 GetWindowSize(const char* windowName) {
    ImGuiWindow* window = ImGui::FindWindowByName(windowName);
    return window ? window->Size : ImVec2(-1, -1); // Return (-1, -1) if not found
}
private:
  GLFWWrapper m_glfw;
  IMGUIWrapper m_imgui;

  int lastTime = 0;
  int deltaTime = 0;
  int currentTime = 0;
  int m_menuWidth = 200;
  bool m_showDemoWindow = true;
};

#endif